#include <iostream>
#include <utility>
#include <memory>

template<class...Ts>
using void_t = std::conditional_t<true,void,std::tuple<Ts...>>;
template<class T>using type=T;
struct unused_type {};

template<class Sig,class=void>
struct is_invokable:std::false_type {};
template<class F, class... Ts>
struct is_invokable<
    F(Ts...),
    void_t<decltype(std::declval<F>()(std::declval<Ts>()...))>
>:std::true_type {};

#define RETURNS(...) decltype(__VA_ARGS__){return (__VA_ARGS__);}

template<class D>
struct rvalue_invoke_support {
  D* self(){return static_cast<D*>(this);}
  D const* self()const{return static_cast<D const*>(this);}

  template<class...Args>
  auto operator()(Args&&...args)&->
  RETURNS( invoke( *self(), std::forward<Args>(args)... ) )

  template<class...Args>
  auto operator()(Args&&...args)const&->
  RETURNS( invoke( *self(), std::forward<Args>(args)... ) )

  template<class...Args>
  auto operator()(Args&&...args)&&->
  RETURNS( invoke( std::move(*self()), std::forward<Args>(args)... ) )

  template<class...Args>
  auto operator()(Args&&...args)const&&->
  RETURNS( invoke( std::move(*self()), std::forward<Args>(args)... ) )
};

// This conditionally forwards a member of the type T
// it is a helper for the function below
template<class T>
struct forward_member_t {
    template<class U>
    decltype(auto) operator()(U&& u)const { return std::move(u); }
};
template<class T>
struct forward_member_t<T&&>:forward_member_t<T>{};

template<class T>
struct forward_member_t<T&> {
    template<class U>
    U&& operator()(U&& u)const { return std::forward<U>(u); }
};

// Use:
// forward_member<T>(t.foo) will move foo if T&& is an rvalue reference
// If the U&& passed in is an rvalue reference, it will also return U&&
template<class T, class U>
auto forward_member( U&& u ) {
    return forward_member_t<T>{}(std::forward<U>(u));
}

namespace curryDetails {
    
    // Curry helper is sort of a manual lambda.  It captures a function and one argument
    // It isn't written as a lambda so we can enable proper rvalue forwarding when it is
    // used in an rvalue context, which is important when currying:
    template<class F, class T>
    struct curry_helper:rvalue_invoke_support<curry_helper<F,T>> {
        F f;
        T t;
        template<class A, class B>
        curry_helper(A&& a, B&& b):f(std::forward<A>(a)), t(std::forward<B>(b)) {}
        
        template<class curry_helper, class...Args>
        friend auto invoke( curry_helper&& self, Args&&... args)->
        RETURNS( forward_member<curry_helper>(self.f)( forward_member<curry_helper>(self.t), std::forward<Args>(args)... ) )
    };
}

namespace curryNS {

    template<class F>
    struct curry_t:rvalue_invoke_support<curry_t<F>> {
        F f;
        template<class... U>curry_t(U&&...u):f(std::forward<U>(u)...){}

        // the rvalue-ref qualified function type of a curry_t:
        template<class curry>
        using function_type = decltype(forward_member<curry>(std::declval<curry>().f));
        // the next curry type if we chain given a new arg A0:
        template<class curry, class A0>
        using next_curry = curry_t<::curryDetails::curry_helper<std::decay_t<function_type<curry>>, std::decay_t<A0>>>;
    
        // 3 invoke overloads
        // The first is one argument when invoking f with A0 does not work:
        template<class curry, class A0>
        friend auto invoke( curry&& self, A0&&a0 )->
        std::enable_if_t<!is_invokable<function_type<curry>(A0)>::value,decltype(next_curry<curry, A0>{forward_member<curry_t>(self.f),std::forward<A0>(a0)})>
        { return next_curry<curry, A0>{forward_member<curry_t>(self.f),std::forward<A0>(a0)}; }
        
        // This is the 2+ argument overload where invoking with the arguments does not work
        // invoke a chain of the top one:
        template<class curry, class A0, class A1, class... Args>
        friend auto invoke( curry&& self, A0&&a0, A1&& a1, Args&&... args )->
        std::enable_if_t<!is_invokable<function_type<curry>(A0, A1, Args...)>::value,decltype(std::forward<curry>(self)(std::forward<A0>(a0))(std::forward<A1>(a1), std::forward<Args>(args)...))>
        { return std::forward<curry>(self)(std::forward<A0>(a0))(std::forward<A1>(a1), std::forward<Args>(args)...); }
        
        // This is the any number of argument overload when it is a valid call to f:
        template<class curry, class...Args>
        friend auto invoke( curry&& self, Args&&...args )->
        std::enable_if_t<is_invokable<function_type<curry>(Args...)>{}, decltype(forward_member<curry>(self.f)(std::forward<Args>(args)...))>
        { return forward_member<curry>(self.f)(std::forward<Args>(args)...); }

    };
    
}
using curryNS::curry_t;

template<class F>
curry_t<std::decay_t<F>> curry( F&& f ) { return {std::forward<F>(f)}; }

static struct foo_t {
    double operator()(double x, int y, std::nullptr_t, std::nullptr_t)const{std::cout << "first\n"; return x*y;}
    char operator()(char c, int x)const{std::cout << "second\n"; return c+x;}
    void operator()(char const*s)const{std::cout << "hello " << s << "\n";}
} foo;

int main() {
    
	auto f = curry(foo);
    using C = decltype((f));
    std::cout << is_invokable<decltype(f)::function_type<C>(const char(&)[5])>{} << "\n";
    invoke( f, "world" );
    // Call the 3rd overload:
    f("world");
    // testing the ability to "jump over" the second overload:
    std::cout << f(3.14,10,nullptr,nullptr) << "\n";
    // call the 2nd overload:
    auto x = f('a',2);
    std::cout << x << "\n";
    // again:
    x =  f('a')(2);
    std::cout << x << "\n";
    std::cout << is_invokable<decltype(foo)(double, int)>{} << "\n";
    std::cout << is_invokable<decltype(foo)(double)>{} << "\n";
    std::cout << is_invokable<decltype(f)(double, int)>{} << "\n";
    std::cout << is_invokable<decltype(f)(double)>{} << "\n";
    std::cout << is_invokable<decltype(f(3.14))(int)>{} << "\n";
    decltype(std::declval<decltype((foo))>()(std::declval<double>(), std::declval<int>())) y = {3};
    (void)y;
	// std::cout << << "\n";
}

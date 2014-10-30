#include <iostream>
#include <utility>

template<class T>struct voider{using type=void;};
template<class T>using void_t=typename voider<T>::type;

template<class Sig,class=void>
struct is_invokable:std::false_type {};
template<class F, class... Ts>
struct is_invokable<
    F(Ts...),
    void_t<decltype(std::declval<F>()(std::declval<Ts>()...))>
>:std::true_type {};

// Curry helper is sort of a manual lambda.  It captures a function and one argument
// It isn't written as a lambda so we can enable proper rvalue forwarding when it is
// used in an rvalue context, which is important when currying:
template<class F, class T>
struct curry_helper {
    F f;
    T t;
    template<class...Args>
    decltype(std::declval<F const&>()(std::declval<T const&>(), std::declval<Args>()...))
    operator()(Args&&...args)const&
    {
        return f(t, std::forward<Args>(args)...);
    }
    template<class...Args>
    decltype(std::declval<F&>()(std::declval<T const&>(), std::declval<Args>()...))
    operator()(Args&&...args)&
    {
        return f(t, std::forward<Args>(args)...);
    }
    template<class...Args>
    decltype(std::declval<F>()(std::declval<T>(), std::declval<Args>()...))
    operator()(Args&&...args)&&
    {
        return std::move(f)(std::move(t), std::forward<Args>(args)...);
    }
};

template<class T> using type=T;

template<class F>
struct curry_t {
    F f;
    // the non-terminating cases.  We support currying of one argument at a time.  More than one
    // argument is shorthand for chaining one argument at a time:
	template<class Arg,class...Args,class=std::enable_if_t<!is_invokable<type<F const&>(Arg,Args...)>::value>>
	auto operator()(Arg&& arg,Args&&...args)const&
    {
		return curry_t< curry_helper<F, std::decay_t<Arg> >>{{ f, std::forward<Arg>(arg) }}(std::forward<Args>(args)...);
	}
    template<class Arg,class...Args,class=std::enable_if_t<!is_invokable<type<F&>(Arg,Args...)>::value>>
	auto operator()(Arg&& arg,Args&&...args)&
    {
		return curry_t< curry_helper<F, std::decay_t<Arg> >>{{ f, std::forward<Arg>(arg) }}(std::forward<Args>(args)...);
	}
    template<class Arg,class...Args,class=std::enable_if_t<!is_invokable<F(Arg,Args...)>::value>>
	auto operator()(Arg&& arg,Args&&...args)&&
    {
		return curry_t< curry_helper<F, std::decay_t<Arg> >>{{ std::move(f), std::forward<Arg>(arg) }}(std::forward<Args>(args)...);
	}
    
    // The terminating cases.  If we run into a case where the arguments would evaluate, this calls the underlying curried function:
    template<class... Args,class=std::enable_if_t<is_invokable<type<F const&>(Args...)>::value>>
	auto operator()(Args&&... args,...)const&
	{
		return f(std::forward<Args>(args)...);
	}
    template<class... Args,class=std::enable_if_t<is_invokable<type<F&>(Args...)>::value>>
    auto operator()(Args&&... args,...)&
	{
		return f(std::forward<Args>(args)...);
	}
	template<class... Args,class=std::enable_if_t<is_invokable<F(Args...)>::value>>
	auto operator()(Args&&... args,...)&&
	{
		return std::move(f)(std::forward<Args>(args)...);
	}

    // makes the currying operator() easier.  It does mean that a curry_t () invoke "works" and returns itself, which
    // could be bad:
    template<class=std::enable_if_t<!is_invokable<F()>::value>>
    auto operator()()&&{
        return std::move(*this);
    }

};

template<class F>
curry_t<typename std::decay<F>::type> curry( F&& f ) { return {std::forward<F>(f)}; }

static struct {
    double operator()(double x, int y)const{return x*y;}
    char operator()(char c, int x)const{return c+x;}
    void operator()(char const*s)const{std::cout << "hello " << s << "\n";}
} foo;

int main() {
    
	auto f = curry(foo);
    std::cout << f(3.14)(10) << "\n";
    f("world");
    auto x =  f('a',2);
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
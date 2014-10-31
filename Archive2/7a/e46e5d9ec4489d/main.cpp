    #include <type_traits>
    #include <utility>
    
    template<class...>
    struct voider { using type = void; };
    template<class...Ts>
    using void_t = typename voider<Ts...>::type;
    
    template<class T>
    using decay_t = typename std::decay<T>::type;
    
    template<class Sig,class=void>
    struct is_invokable:std::false_type {};
    template<class F, class... Ts>
    struct is_invokable<
      F(Ts...),
      void_t<decltype(std::declval<F>()(std::declval<Ts>()...))>
    >:std::true_type {};
    
    #define RETURNS(...) decltype(__VA_ARGS__){return (__VA_ARGS__);}
    
    template<class D>
    class rvalue_invoke_support {
      D& self(){return *static_cast<D*>(this);}
      D const& self()const{return *static_cast<D const*>(this);}
    public:
      template<class...Args>
      auto operator()(Args&&...args)&->
      RETURNS( invoke( this->self(), std::forward<Args>(args)... ) )
    
      template<class...Args>
      auto operator()(Args&&...args)const&->
      RETURNS( invoke( this->self(), std::forward<Args>(args)... ) )
    
      template<class...Args>
      auto operator()(Args&&...args)&&->
      RETURNS( invoke( std::move(this->self()), std::forward<Args>(args)... ) )
    
      template<class...Args>
      auto operator()(Args&&...args)const&&->
      RETURNS( invoke( std::move(this->self()), std::forward<Args>(args)... ) )
    };
    
    namespace curryDetails {
      // Curry helper is sort of a manual lambda.  It captures a function and one argument
      // It isn't written as a lambda so we can enable proper rvalue forwarding when it is
      // used in an rvalue context, which is important when currying:
      template<class F, class T>
      struct curry_helper: rvalue_invoke_support<curry_helper<F,T>> {
        F f;
        T t;
    
        template<class A, class B>
        curry_helper(A&& a, B&& b):f(std::forward<A>(a)), t(std::forward<B>(b)) {}
    
        template<class curry_helper, class...Args>
        friend auto invoke( curry_helper&& self, Args&&... args)->
        RETURNS( std::forward<curry_helper>(self).f( std::forward<curry_helper>(self).t, std::forward<Args>(args)... ) )
      };
    }
    
    namespace curryNS {
      // the rvalue-ref qualified function type of a curry_t:
      template<class curry>
      using function_type = decltype(std::declval<curry>().f);
    
      template <class> struct curry_t;
    
      // the next curry type if we chain given a new arg A0:
      template<class curry, class A0>
      using next_curry = curry_t<::curryDetails::curry_helper<decay_t<function_type<curry>>, decay_t<A0>>>;
    
      // 3 invoke_ overloads
      // The first is one argument when invoking f with A0 does not work:
      template<class curry, class A0>
      auto invoke_(std::false_type, curry&& self, A0&&a0 )->
      RETURNS(next_curry<curry, A0>{std::forward<curry>(self).f,std::forward<A0>(a0)})
    
      // This is the 2+ argument overload where invoking with the arguments does not work
      // invoke a chain of the top one:
      template<class curry, class A0, class A1, class... Args>
      auto invoke_(std::false_type, curry&& self, A0&&a0, A1&& a1, Args&&... args )->
      RETURNS(std::forward<curry>(self)(std::forward<A0>(a0))(std::forward<A1>(a1), std::forward<Args>(args)...))
    
      // This is the any number of argument overload when it is a valid call to f:
      template<class curry, class...Args>
      auto invoke_(std::true_type, curry&& self, Args&&...args )->
      RETURNS(std::forward<curry>(self).f(std::forward<Args>(args)...))
    
      template<class F>
      struct curry_t : rvalue_invoke_support<curry_t<F>> {
        F f;
    
        template<class... U>curry_t(U&&...u):f(std::forward<U>(u)...){}
    
        template<class curry, class...Args>
        friend auto invoke( curry&& self, Args&&...args )->
        RETURNS(invoke_(is_invokable<function_type<curry>(Args...)>{}, std::forward<curry>(self), std::forward<Args>(args)...))
      };
    }
    
    template<class F>
    curryNS::curry_t<decay_t<F>> curry( F&& f ) { return {std::forward<F>(f)}; }
    
    #include <iostream>
    
    static struct foo_t {
      double operator()(double x, int y, std::nullptr_t, std::nullptr_t)const{std::cout << "first\n"; return x*y;}
      char operator()(char c, int x)const{std::cout << "second\n"; return c+x;}
      void operator()(char const*s)const{std::cout << "hello " << s << "\n";}
    } foo;
    
    int main() {
    
      auto f = curry(foo);
      using C = decltype((f));
      std::cout << is_invokable<curryNS::function_type<C>(const char(&)[5])>{} << "\n";
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
    

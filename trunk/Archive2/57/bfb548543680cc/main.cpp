    #include <iostream>
    #include <functional>
    #include <string>
     
    namespace fx {
    template<int I> struct placeholder{};
    }
     
    namespace std{
    template<int I>
    struct is_placeholder< ::fx::placeholder<I>> : std::integral_constant<int, I>{};
    }
     
    namespace fx {
    template <size_t... Is>
    struct indices {};
     
    template <size_t N, std::size_t... Is>
    struct build_indices : build_indices<N-1, N-1, Is...> {};
     
    template <size_t... Is>
    struct build_indices<0, Is...> : indices<Is...> {};
     
    template<std::size_t... Is, class F, class... Args>
    auto easy_bind(indices<Is...>, F const& f, Args&&... args)
    -> decltype(std::bind(f, std::forward<Args>(args)..., placeholder<Is + 1>{}...))
    {
    return std::bind(f, std::forward<Args>(args)..., placeholder<Is + 1>{}...);
    }
     
    template<class R, class... FArgs, class... Args>
    auto easy_bind(std::function<R(FArgs...)> f, Args&&... args)
    -> decltype(fx::easy_bind(build_indices<sizeof...(FArgs) - sizeof...(Args)>{}, f, std::forward<Args>(args)...)) {
    return fx::easy_bind(build_indices<sizeof...(FArgs) - sizeof...(Args)>{}, f, std::forward<Args>(args)...);
    }
    }
     
    //Test Case:
    struct SomeStruct {
    public:
    void function(int x, float y, std::string str) {
    std::cout << x << " " << y << " " << str << std::endl;
    }
    };
     
    using Functor = std::function<void(SomeStruct*,int,float,std::string)>;
    
    template <typename R, typename ...Args>
    std::function<void(R*,Args...)> proxycall(void (R::*mf)(Args...))
    {
        return std::function<void(R*,Args...)>(mf);
    }
     
    int main() {
    Functor functor = &SomeStruct::function;
    auto func1 = fx::easy_bind(functor, new SomeStruct);
    func1(5, 2.5, "Test1");
     
    auto func2 = fx::easy_bind(Functor(&SomeStruct::function), new SomeStruct);
    func2(5, 2.5, "Test2");
     
     SomeStruct test;
    auto func3 = fx::easy_bind(proxycall(&SomeStruct::function), new SomeStruct);
    func3(5, 2.5, "Test3");
     
    return 0;
    }
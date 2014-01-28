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
    int function(int x, float y, std::string str) {
    std::cout << x << " " << y << " " << str << std::endl;
    return 42;
    }
    };
    
    template <typename Ret, typename Struct, typename ...Args>
    std::function<Ret (Struct*,Args...)> proxycall(Ret (Struct::*mf)(Args...))
    {
        return std::function<Ret (Struct*,Args...)>(mf);
    }
     
    int main() {
        auto func3 = fx::easy_bind(proxycall(&SomeStruct::function), new SomeStruct);
        int ret = func3(5, 2.5, "Test3");
        std::cout << ret << "\n";
     
        return 0;
    }
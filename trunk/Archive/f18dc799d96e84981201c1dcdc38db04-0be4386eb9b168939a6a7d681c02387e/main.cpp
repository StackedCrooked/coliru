    #include <type_traits>

    template<typename F>
    struct num_args;

    template<typename C, typename R, typename... Args>
    struct num_args<R (C::*)(Args...)> : std::integral_constant<int, sizeof...(Args)> { };

    struct X
    {
        void operator () (int, int) { }
    };

    int main(void)
    {
        X x;
        static_assert(num_args<decltype(&decltype(x)::operator())>::value == 2, "!");

        auto l = [](int, int){};
        static_assert(num_args<decltype(&decltype(l)::operator())>::value == 2, "!");
    }

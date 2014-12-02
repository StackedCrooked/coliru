    #include <tuple>
    
    template <int N>
    struct Disc {};
    
    template <typename T>
    struct pop;
    
    template <typename E, typename... Ts>
    struct pop<std::tuple<E, Ts...>> {
        using type = decltype(
            std::tuple_cat(
                std::declval<std::tuple<E>>(),
                std::declval<typename pop<std::tuple<Ts...>>::type>()
            )
        );
    };
    
    template <typename E>
    struct pop<std::tuple<E>> {
        using type = std::tuple<>;
    };

    static_assert(
        std::is_same<
            pop<std::tuple<Disc<2>, Disc<1>>>::type,
            std::tuple<Disc<2>>
        >::value, "pop<> not working. (1)"
    );
    
    static_assert(
        std::is_same<
            pop<std::tuple<Disc<2>>>::type,
            std::tuple<>
        >::value, "pop<> not working. (2)"
    );
    
    template <typename T>
    struct top;
    
    template <typename... Ts>
    struct top<std::tuple<Ts...>> {
        static const std::size_t idx = std::tuple_size<std::tuple<Ts...>>::value-1;
        using type = typename std::tuple_element<idx, std::tuple<Ts...>>::type;
    };

    static_assert(
        std::is_same<
            typename top<std::tuple<Disc<2>, Disc<1>>>::type,
            Disc<1>
        >::value, "top<> not working."
    );
    
    template <typename T, typename E>
    struct push;
    
    template <typename... Ts, typename E>
    struct push<std::tuple<Ts...>, E> {
        using type = decltype(
            std::tuple_cat(
                std::declval<std::tuple<Ts...>>(),
                std::declval<std::tuple<E>>()
            )
        );
    };
    
    static_assert(
        std::is_same<
            typename push<std::tuple<Disc<2>>, Disc<1>>::type,
            std::tuple<Disc<2>, Disc<1>>
        >::value, "push<> not working."
    );
    
    template <typename T1, typename T2, typename T3>
    struct hanoi;
    
    template <typename... Ts1, typename... Ts2, typename... Ts3>
    struct hanoi<std::tuple<Ts1...>, std::tuple<Ts2...>, std::tuple<Ts3...>> {
        using stack1 = std::tuple<Ts1...>;
        using stack2 = std::tuple<Ts2...>;
        using stack3 = std::tuple<Ts3...>;
    };
    
    template<typename H, int F, int T>
    struct move_disc;
    
    template<typename H>
    struct move_disc<H, 1, 2> {
        using type = hanoi<
            typename pop<typename H::stack1>::type,
            typename push<
                typename H::stack2,
                typename top<typename H::stack1>::type>
            ::type,
            typename H::stack3
        >;
    };
    
    template <typename T>
    struct TD;
    
    int main() {
    }
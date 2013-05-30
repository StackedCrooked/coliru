    #include <iostream>
    #include <array>
    #include <functional>

    namespace detail
    {
        template<int... Is>
        struct seq { };

        template<int N, int... Is>
        struct gen_seq : gen_seq<N - 1, N - 1, Is...> { };

        template<int... Is>
        struct gen_seq<0, Is...> : seq<Is...> { };
    }

    template<int N, typename T>
    struct Container {
        template<typename... Ts>
        Container(Ts&&... vs) : data{{std::forward<Ts>(vs)...}} {
            static_assert(sizeof...(Ts)==N,"Not enough args supplied!");
        }

        template<typename F>
        void doOperation(F&& func)
        {
            doOperation(std::forward<F>(func), detail::gen_seq<N>());
        }

        template<typename F, int... Is>
        void doOperation(F&& func, detail::seq<Is...>)
        {
            (std::forward<F>(func))(data[Is]...);
        }

        std::array<T,N> data;
    };
    
    struct my_functor
    {
        void operator () (int, int, int) && { std::cout << "rvalue" << std::endl; }
        void operator () (int, int, int) & { std::cout << "lvalue" << std::endl; }
    };

    int main(void)
    {
        Container<3,int> cont(1,2,3);

        cont.doOperation(my_functor());
        
        my_functor f;
        cont.doOperation(f);

        return 0;
    }

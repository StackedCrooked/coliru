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

    int main(void)
    {
        Container<3,int> cont(1,2,3);

        double sum = 0.0;
        cont.doOperation([&sum](int x, int y, int z)->void{
            sum += x;
            sum += y;
            sum += z;
        });

        std::cout << sum << std::endl;

        return 0;
    }

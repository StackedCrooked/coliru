#include <iostream>

namespace detail {
    template<size_t N>
    struct bar_helper {
        template<typename... Ts>
        static void bar() {
            std::cout << "Generic\n";
        }
    };

    template<>
    struct bar_helper<0> {
        template<typename... Ts>
        static void bar() {
            std::cout << "Specialized\n";
        }
    };
}

template <typename... Ts>
struct foo
{
    template <size_t N>
    void bar() { detail::bar_helper<N>::template bar<Ts...>(); }
};

int main()
{
    foo<int, float>{}.bar<0>();
}

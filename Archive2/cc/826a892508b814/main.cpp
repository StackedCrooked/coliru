#include <iostream>
#include <utility>
#include <array>

    template<class T, size_t... sizes>
    struct multi_array_helper {
      using type=T;
    };
    template<class T, size_t... sizes>
    using multi_array = typename multi_array_helper<T, sizes...>::type;

    template<class T, size_t s0, size_t... sizes>
    struct multi_array_helper<T, s0, sizes...> {
      using type=std::array<multi_array<T, sizes...>, s0> ;
    };

int main()
{
    multi_array<int, 3,2> foo = {{ {{0,1}}, {{0}}, {{1,2}} }};
    for (auto&& a:foo)
        for (auto&& x:a)
            std::cout << x << '\n';
}
#include <array>

template <typename T, std::size_t...Extents>
struct build_array_type {
    using type = T;
};
template <typename T, std::size_t First, std::size_t...Rest>
struct build_array_type<T, First, Rest...> {
    using type = std::array<typename build_array_type<T, Rest...>::type, First>;
};
template <typename T, std::size_t...Extents>
using multiarray = typename build_array_type<T, Extents...>::type;

int main() {
    auto foo = multiarray<int, 2, 3, 4>{{
        {{ {{  0,  1,  2,  3 }},
           {{  4,  5,  6,  7 }},
           {{  8,  9, 10, 11 }} }},
        {{ {{ 12, 13, 14, 15 }},
           {{ 16, 17, 18, 19 }},
           {{ 20, 21, 22, 23 }} }}
    }};
    foo[1][2][3] = 2;
}

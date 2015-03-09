#include <type_traits>
#include <vector>

template <typename T>
struct dimension : std::integral_constant<std::size_t, 0> {};

template <typename T, typename A>
struct dimension<std::vector<T, A>> : std::integral_constant<std::size_t, 1 + dimension<T>{}> {};

int main()
{
    std::vector<int> v1d;
    std::vector<std::vector<int>> v2d;
    std::vector<std::vector<std::vector<int>>> v3d;
    
    static_assert(dimension<decltype(v1d)>{} == 1, "!");
    static_assert(dimension<decltype(v2d)>{} == 2, "!");
    static_assert(dimension<decltype(v3d)>{} == 3, "!");
}

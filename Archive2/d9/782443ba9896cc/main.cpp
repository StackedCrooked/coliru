#include <iostream>
#include <array>
#include <cstring>

template <int... > struct seq {};

template <typename, int...> struct NArray;

template <typename T, int N>
struct NArray<T, N> {
    using type = std::array<T, N>;
};

template <typename T, int FIRST, int... REST>
struct NArray<T, FIRST, REST...> {
    using type = std::array<typename NArray<T, REST...>::type, FIRST>;
};

template <typename T, typename Dim>
struct make_narray;

template <typename T, int... N>
struct make_narray<T, seq<N...>>
{
    using type = typename NArray<T, N...>::type;
};

template <typename T>
T& get(T& val, seq<>)
{
    return val;
}

template <typename NA, int E0, int... Es>
auto get(NA& arr, seq<E0, Es...>)
-> decltype(get(arr[E0], seq<Es...>{}))
{
    return get(arr[E0], seq<Es...>{});
}

template <typename T, typename Dim, typename... Elems>
typename make_narray<T, Dim>::type
NDimensionalArray(T val)
{
    typename make_narray<T, Dim>::type narray{};
    auto _{get(narray, Elems{}) = val ...};  // Quick initialization step!
    return narray;
}

int main() {
    auto a = NDimensionalArray<bool, seq<2, 4, 5, 3>, seq<1, 2, 3, 2>, seq<0, 0, 2, 1>>(true);

    std::cout << std::boolalpha;
    std::cout << a[0][0][0][0] << std::endl; // prints false
    std::cout << a[1][2][3][2] << std::endl; // prints true
    std::cout << a[0][0][2][1] << std::endl; // prints true
}
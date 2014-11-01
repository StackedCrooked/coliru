#include <iostream>
#include <iomanip>
#include <array>
#include <tuple>
#include <utility>
#include <type_traits>

template <typename, int, int...> struct NArray;

template <typename T, int NUM_DIMENSIONS, int N>
struct NArray<T, NUM_DIMENSIONS, N>
{
    using type = std::array<T, N>;
};

template <typename T, int NUM_DIMENSIONS, int FIRST, int... REST>
struct NArray<T, NUM_DIMENSIONS, FIRST, REST...>
{
    using type = std::array<typename NArray<T, NUM_DIMENSIONS, REST...>::type, FIRST>;
};

template <typename A, typename T>
void assign(A& arr, const T& value)
{
    arr = value;
}

template <int I, int... Is, typename A, typename T>
void assign(A& arr, const T& value)
{
    assign<Is...>(arr[I], value);
}

template <int SIZE, int PACK, int... Ind, typename T, typename A, std::size_t... Is>
auto set(const T& value, A& arr, std::index_sequence<Is...> seq)
    -> std::enable_if_t<(SIZE*PACK == sizeof...(Ind))>
{    
}

template <int SIZE, int PACK, int... Ind, typename T, typename A, std::size_t... Is>
auto set(const T& value, A& arr, std::index_sequence<Is...> seq)
    -> std::enable_if_t<(SIZE*PACK < sizeof...(Ind))>
{    
    constexpr auto t = std::make_tuple(Ind...);
    assign<std::get<PACK*SIZE+Is>(t)...>(arr, value);
    set<SIZE, PACK+1, Ind...>(value, arr, seq);
}

template <typename T, int DIMS, int... N, std::size_t... Is>
auto make_narray(const T& value, std::index_sequence<Is...> seq)
{
    constexpr auto t = std::make_tuple(N...);
    typename NArray<T, DIMS, std::get<Is>(t)...>::type arr;
    set<DIMS, 1, N...>(value, arr, seq);
    return arr;
}

template <typename T, int DIMS, int... N>
auto NDimensionalArray(const T& value)
{    
    return make_narray<T, DIMS, N...>(value, std::make_index_sequence<DIMS>{});
}

int main()
{
    auto a = NDimensionalArray<bool,4, 2,4,5,3, 1,2,3,2, 0,0,2,1>(true);
    std::cout << std::boolalpha;
    std::cout << a[1][2][3][2] << std::endl; // ~~~~^
    std::cout << a[0][0][2][1] << std::endl; // ~~~~~~~~~~~~^
    std::cout << a[0][0][0][0] << std::endl; // (not set)
}

#include <iostream>
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
void s(A& a, T value)
{
    a = value;
}

template <int I, int... Is, typename A, typename T>
void s(A& a, T value)
{
    s<Is...>(a[I], value);
}

template <int SIZE, int PACK, int... Ind, typename T, typename A, std::size_t... Is>
auto set(T value, A& arr, std::index_sequence<Is...> seq)
    -> std::enable_if_t<(SIZE*PACK==sizeof...(Ind))>
{
    
}

template <int SIZE, int PACK, int... Ind, typename T, typename A, std::size_t... Is>
auto set(T value, A& arr, std::index_sequence<Is...> seq)
    -> std::enable_if_t<(SIZE*PACK<sizeof...(Ind))>
{    
    constexpr auto t = std::make_tuple(Ind...);
    s<std::get<PACK*SIZE+Is>(t)...>(arr, value);
    set<SIZE, PACK+1, Ind...>(value, arr, seq);
}

template <typename T, int NUM_DIMENSIONS, int... N, std::size_t... Is>
auto _NDimensionalArray(T value, std::index_sequence<Is...> seq)
{
    constexpr auto t = std::make_tuple(N...);
    typename NArray<T, NUM_DIMENSIONS, std::get<Is>(t)...>::type nArray;
    set<NUM_DIMENSIONS, 1, N...>(value, nArray, seq);
    return nArray;
}

template <typename T, int NUM_DIMENSIONS, int... N>
auto NDimensionalArray(T value)
{    
    return _NDimensionalArray<T, NUM_DIMENSIONS, N...>(value, std::make_index_sequence<NUM_DIMENSIONS>{});
}

int main()
{
    const auto nArray = NDimensionalArray<int,4, 2,4,5,3, 0,0,0,0, 1,1,1,1>(42);
    std::cout << nArray[0][0][0][0] << std::endl;
    std::cout << nArray[1][1][1][1] << std::endl;
}

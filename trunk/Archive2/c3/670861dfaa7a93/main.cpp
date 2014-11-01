#include <iostream>
#include <iomanip>
#include <array>
#include <tuple>
#include <utility>
#include <type_traits>
#include <cstddef>

template <std::size_t... Is>
struct index_sequence {};

template <std::size_t N, std::size_t... Is>
struct make_index_sequence_h : make_index_sequence_h<N - 1, N - 1, Is...> {};

template <std::size_t... Is>
struct make_index_sequence_h<0, Is...>
{
    using type = index_sequence<Is...>;
};

template <std::size_t N>
using make_index_sequence = typename make_index_sequence_h<N>::type;

template <std::size_t I, class Seq>
struct sequence_element;

template <std::size_t I, std::size_t E, std::size_t... Es>
struct sequence_element<I, index_sequence<E, Es...>> : sequence_element<I - 1, index_sequence<Es...>>::type {};

template <std::size_t E, std::size_t... Es>
struct sequence_element<0, index_sequence<E, Es...>> : std::integral_constant<std::size_t, E> {};

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
auto set(const T& value, A& arr, index_sequence<Is...> seq)
    -> typename std::enable_if<(SIZE*PACK == sizeof...(Ind))>::type
{    
}

template <int SIZE, int PACK, int... Ind, typename T, typename A, std::size_t... Is>
auto set(const T& value, A& arr, index_sequence<Is...> seq)
    -> typename std::enable_if<(SIZE*PACK < sizeof...(Ind))>::type
{    
    using Seq = index_sequence<Ind...>;
    assign<sequence_element<PACK*SIZE+Is, Seq>::value...>(arr, value);
    set<SIZE, PACK+1, Ind...>(value, arr, seq);
}

template <typename T, int DIMS, typename Seq, int... N>
struct narray_signature;

template <typename T, int DIMS, std::size_t... Is, int... N>
struct narray_signature<T, DIMS, index_sequence<Is...>, N...>
{
    using Seq = index_sequence<N...>;
    using type = typename NArray<T, DIMS, sequence_element<Is, Seq>::value...>::type;
};

template <typename T, int DIMS, int... N, std::size_t... Is>
auto make_narray(const T& value, index_sequence<Is...> seq)
    -> typename narray_signature<T, DIMS, make_index_sequence<DIMS>, N...>::type
{
    using Seq = index_sequence<N...>;
    typename NArray<T, DIMS, sequence_element<Is, Seq>::value...>::type arr{};
    set<DIMS, 1, N...>(value, arr, seq);
    return arr;
}

template <typename T, int DIMS, int... N>
auto NDimensionalArray(const T& value)
    -> typename narray_signature<T, DIMS, make_index_sequence<DIMS>, N...>::type
{    
    return make_narray<T, DIMS, N...>(value, make_index_sequence<DIMS>{});
}

int main()
{
    auto a = NDimensionalArray<bool,4, 2,4,5,3, 1,2,3,2, 0,0,2,1>(true);
    std::cout << std::boolalpha;
    std::cout << a[1][2][3][2] << std::endl; // ~~~~^
    std::cout << a[0][0][2][1] << std::endl; // ~~~~~~~~~~~~^
    std::cout << a[0][0][0][0] << std::endl; // (not set)
}

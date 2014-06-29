#include <iostream>
#include <vector>
#include <tuple>
#include <utility>

using namespace std;

template<typename T, size_t N>
struct VectorGenerator
{
    typedef std::vector< typename VectorGenerator<T, N-1>::type > type;
};

template<typename T>
struct VectorGenerator<T, 0>
{
    typedef std::vector<T> type;
};

// Alias for V3, V2 ... usage
using V3 = VectorGenerator<double, 3>::type;
using V2 = VectorGenerator<double, 2>::type;

// Alias for V <k> usage
template <size_t N> 
using V = typename VectorGenerator<double, N>::type;

template <typename T>
struct identity { using type = T; };

// Generate a tuple of towers by mapping index_sequence over gen_tower.
template <typename T, std::size_t... Is>
std::tuple<VectorGenerator<T, Is>...> gen_towers_impl(std::index_sequence<Is...>);

// Make an index_sequence for N and use gen_towers_impl.
template <typename T, std::size_t N>
struct gen_towers
    : identity<decltype(gen_towers_impl<T>(std::make_index_sequence<N>()))> {};

// Convenience type aliases
template <typename T, std::size_t N>
using gen_towers_t = typename gen_towers<T, N>::type;

int main() {

    // Generate towers
    V<3> v3;
    V<2> v2;
    v3.push_back(v2);
    V<1> v1;
    
    // generate tower tuples
    gen_towers_t<double, 3> tower2;
    auto tower = std::tuple<V<1>, V<2>, V<3>>(v1, v2, v3);
    return 0;
}
#include <tuple>
#include <cstddef>

template<size_t... Ns>
struct indices { using type = indices; };

template<size_t N, size_t... Ns>
struct build_indices : build_indices<N-1, N-1, Ns...> {};

template<size_t... Ns>
struct build_indices<0, Ns...> : indices<Ns...> {};

template<typename T, size_t Index>
using Depend = T;

template<typename T, size_t N, typename I = typename build_indices<N>::type>
struct repeat;

template<typename T, size_t N, size_t... Indices>
struct repeat<T, N, indices<Indices...>> {
    using type = std::tuple<Depend<T, Indices>...>;
};

int main() {
    repeat<int, 3>::type x;
    std::get<0>(x);
}


#include <memory>
#include <iostream>
#include <tuple>
#include <type_traits>

template<size_t... Ns>
struct indices { typedef indices type; };

template<size_t N, size_t... Ns>
struct build_indices : build_indices<N - 1, N - 1, Ns...> {};

template<size_t... Ns>
struct build_indices<0, Ns...> : indices<Ns...> {};

template<size_t N, size_t... Ns>
struct build_reverse_indices : build_reverse_indices<N - 1, Ns..., N - 1> {};

template<size_t... Ns>
struct build_reverse_indices<0, Ns...> : indices<Ns...> {};

int main() {
    struct {} _ = build_indices<3>::type{};
    struct {} r_ = build_reverse_indices<3>::type{};
}
#include <iostream>
#include <array>

const std::size_t SIZE = 10;

// int sequence
template <int... I>
struct sizes { using type = sizes <I...>; };

// construction of range [0, S] as int sequence
template <int S, int... I>
struct range_t : range_t <S - 1, S, I...> { };

template <int... I>
struct range_t <0, I...> : sizes <0, I...> { };

template <int S>
using range = typename range_t <S - 1>::type;

// is number Q in int sequence [A, An...]?
template <int Q>
constexpr bool in() { return false; }

template <int Q, int A, int... An>
constexpr bool in() { return Q == A || in <Q, An...>(); }

// convert int sequence [A...] to array<bool, sizeof...(N)>
template <int... A, int... N>
std::array<bool, sizeof...(N)>
func(sizes <N...>) {
    return std::array<bool, sizeof...(N)>{{in <N, A...>()...}};
}

template <int... A>
std::array<bool, SIZE>
func() {
    return func <A...>(range <SIZE>());
}

int main() {
    std::array<bool, SIZE> b = func<SIZE, 1,3,7>();
    // I want b[1]=true, b[3] = true, b[7] = true, all others false
    for (int x: b) std::cout << x << std::endl;
}

#include <cstddef>
#include <climits>
#include <array>
#include <limits>

namespace detail {
constexpr size_t pow(size_t base, size_t exponent) {
    return exponent == 0 ? 1 : (base * pow(base, exponent - 1));
}
template<size_t... Ns>
struct indices {};

template<size_t N, size_t... Ns>
struct build_indices : build_indices<N-1, N-1, Ns...> {};

template<size_t... Ns>
struct build_indices<0, Ns...> : indices<Ns...> {};

template<size_t N>
struct generate_array {
    template<size_t... Indices>
    static constexpr std::array<size_t, N> generate(indices<Indices...>) {
        return std::array<size_t, N>{{pow(10, Indices)...}};
    }

    static constexpr std::array<size_t, N> value = generate(build_indices<N>{});
};
} // detail

template<typename Digit = unsigned int, typename Digits = unsigned long long>
struct uintx {
private:
    static constexpr size_t digit_bits = CHAR_BIT * sizeof(Digit);
public:
    static constexpr size_t digits10 = std::numeric_limits<Digit>::digits10;
    static constexpr size_t base = detail::pow(10, digits10);
    static constexpr std::array<size_t, digits10> powers_of_ten = detail::generate_array<digits10>::value;
};

#include <iostream>

int main() {
    uintx<> stuff;
    for(auto&& i : stuff.powers_of_ten)
        std::cout << i << '\n';
}
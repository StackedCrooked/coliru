#include <initializer_list>
#include <utility>

template <typename T, std::size_t N>
struct array {
    T elems[N];
    
    constexpr const T& operator[] (std::size_t i) const { return elems[i]; }
    constexpr T& operator[] (std::size_t i) { return elems[i]; }
};

template <typename T, std::size_t...Is>
constexpr T double_sum_of(std::index_sequence<Is...>) {
    array<T, sizeof...(Is)> foo = {{ Is... }};
    for (auto i = sizeof...(Is); i-- > 0;) {
        foo[i] *= 2;
    }
    T sum{};
    for (auto i = sizeof...(Is); i-- > 0;) {
        sum += foo[i];
    }
    return sum;
}

// Returns twice the sum of the Ts less than N
template <typename T, T N>
constexpr T double_sum_of() {
    return double_sum_of<T>(std::make_index_sequence<N>{});
}

int main() {
    constexpr int i = double_sum_of<int, 10>();
    return i;
}

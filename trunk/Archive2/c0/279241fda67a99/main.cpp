#include <initializer_list>
#include <utility>

template <typename T, std::size_t N>
struct array {
    T elems[N];
    
    constexpr const T& operator[] (std::size_t i) const { return elems[i]; }
    constexpr T& operator[] (std::size_t i) { return elems[i]; }
};

template <typename T, std::size_t...Is>
constexpr T sum_of(std::index_sequence<Is...>) {
    array<T, sizeof...(Is)> foo = {{ Is... }};
    foo[1] += 42;
    T sum{};
    for (auto i = sizeof...(Is); i-- > 0;) {
        sum += foo[i];
    }
    return sum;
}

template <typename T, std::size_t N>
constexpr T sum_of() {
    return sum_of<T>(std::make_index_sequence<N>{});
}

int main() {
    constexpr int i = sum_of<int, 10>();
    return i;
}

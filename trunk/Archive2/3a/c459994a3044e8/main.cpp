#include <utility>
#include <array>

template<typename T, size_t N, std::size_t... I>
std::array<T, N> make_indexed_array_helper(std::integer_sequence<size_t, I...>) {
    return std::array<T, N>{{T(I)...}};
}

template<typename T, std::size_t N>
std::array<T, N> make_indexed_array() {
    return make_indexed_array_helper<T, N>(std::make_index_sequence<N>{});
}

class Element {
    std::size_t idx;

public:
    constexpr Element(std::size_t index) noexcept : idx(index) {}

    constexpr std::size_t index() const noexcept { return idx; }
};

#include <iostream>

int main() {
    auto arr = make_indexed_array<Element, 5>();
    for(const auto& e : arr)
        std::cout << e.index() << ' ';
    std::cout << std::endl;
}

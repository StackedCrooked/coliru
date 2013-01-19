#include <limits>

template <
    typename T,
    std::size_t N,
    bool = static_cast<std::size_t>(std::numeric_limits<T>::max()) < N>
struct validator {
    static constexpr bool validate(T value) {
        return static_cast<std::size_t>(value) < N;
    }
};

template <typename T, std::size_t N>
struct validator<T, N, true> {
    static constexpr bool validate(T) {
        return true;
    }
};

int main() {
    // Works
    static_assert(validator<int, 4>::validate(3), "Invalid");
    // Error :-(
    static_assert(validator<bool, 2>::validate(true), "Invalid");
}

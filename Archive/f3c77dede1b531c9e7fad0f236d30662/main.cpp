#include <iostream>
#include <limits>

template <std::size_t N>
struct X { };

namespace std {
    template <std::size_t N>
    struct numeric_limits<X<N>> {
        static constexpr int log(int n) {
            return n == 1 ? 0 : log(n >> 1) + 1;
        }

        static constexpr int digits = log(N) + 1;
    };
}

int main() {
    int const* x = &std::numeric_limits<int>::digits;
    int const* y = &std::numeric_limits<X<8>>::digits;

    std::cout << *x << " " << *y << "\n";
}

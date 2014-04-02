#include <iostream>

template <typename T>
inline
constexpr T Factor(T n) {
    return (999 / n) * (999 / n + 1);
}

template <typename T>
inline 
constexpr T SumMulti(T n) {
    return n * Factor(n) / 2;
}
 
int main() {
    std::cout << SumMulti(3) + SumMulti(5) - SumMulti(15);
}
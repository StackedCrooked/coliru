#include <iostream>
#include <type_traits>

template<int N, int N3 = N % 3, int N5 = N % 5>
struct helper {
    static constexpr int value() {
        return 0;
    }
};

template<int N>
struct helper<N,0,0> {
    static constexpr int value() {
        return N;
    }
};

template<int N, int N5>
struct helper<N,0,N5> {
    static constexpr int value() {
        return 0;
    }
};

template<int N, int N3>
struct helper<N,N3,0> {
    static constexpr int value() {
        return 0;
    }
};

template<int i>
struct Sum : std::integral_constant<int, helper<i>::value() + helper<i-1>::value()> {};

int main() {
    std::cout << Sum<1000>::value;
}
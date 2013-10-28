#include <iostream>

template<typename T = unsigned long long>
inline T fibonacci(T number) {
    T a(1);
    T b(0);
    T c(0);

    while(number--) {
        c = b;
        b = a;
        a = b + c;
    }

    return a;
}

constexpr unsigned long long fib(unsigned long long x) {
    return x == 0 ? 0 : x == 1 ? 1 : fib(x - 1) + fib(x - 2); 
}

int main() {
    for(unsigned i = 0; i < 30; ++i) {
        std::cout << i + 1 << ") " << fibonacci(i) << " vs " << fib(i) << '\n';
    }
}
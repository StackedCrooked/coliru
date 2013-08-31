#include <iostream>

using ull = unsigned long long;

ull operator"" _fact(ull in) {
    ull total = 1;
    for(ull i = 1; i <= in; i++)
        total *= i;
    return total;
}

int main() {
    std::cout << 10_fact;
}

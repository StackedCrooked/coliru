#include <iostream>

constexpr unsigned long long f(int first, int second, int sum = 0, int limit = 4000000) {
    return limit <= 0 ? 
        sum + 1 
        : f(second,
        first + second,
        second % 2 == 1 ? sum + second : sum,
        limit - second);
}

int main() {
    std::cout << f(1,1);
}
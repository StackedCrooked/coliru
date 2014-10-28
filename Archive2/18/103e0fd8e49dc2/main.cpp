#include <iostream>
#include <tuple>
#include <vector>
#include <set>

template<typename T, typename... Ts>
struct Index {};

template<typename T, typename T1, typename... Ts>
struct Index<T, T1, Ts...> {
    static const size_t value = 1 + Index<T, Ts...>::value;
};

template<typename T, typename... Ts>
struct Index<T, T, Ts...> {
    static const size_t value = 0;
};

int main() {
    std::cout << Index<std::vector<int>, double, int, std::vector<int>, std::set<float>, bool>::value;
    return 0;
}


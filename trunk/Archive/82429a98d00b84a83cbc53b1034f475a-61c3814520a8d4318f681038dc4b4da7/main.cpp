#include <iostream>
#include <vector>

template <typename T, typename... U, typename V>
void f(V) {
    std::cout << sizeof...(U) << '\n';
}

int main() {
    f<int, double>(1.0);
    f<int, double>(std::vector<int>());
}
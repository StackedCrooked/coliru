#include <iostream>

template<typename T>
void print_all(T x) {
    std::cout << x << '\n';
}

template<typename T, typename... Ts>
void print_all(T x, Ts... ts) {
    std::cout << x << ' ';
    print_all(x, ts...);
}

int main() {
    print_all(1, 2, 3, 4, "5", 6, 7, 8.0, 9, 10, true, nullptr);
}

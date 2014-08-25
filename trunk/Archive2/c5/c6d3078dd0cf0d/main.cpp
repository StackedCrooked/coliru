#include <iostream>

template <typename T, typename U>
auto add(T x, U y) -> decltype(x + y) {
    return x + y;
}

auto main() -> int {
    std::cout << "Lidl: " << add(2, 4.6);
}

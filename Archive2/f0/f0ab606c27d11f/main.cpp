#include <iostream>

auto main() -> int {
    decltype(auto) fn = [&](auto arg) {
        return arg * arg;
    };
    decltype(auto) result = fn(9001);
    std::cout << result;
}
#include <iostream>
#include <tuple>

void test(const std::tuple<int, int, int>& x) {
    std::cout << std::get<0>(x) << ' ' << std::get<1>(x) << ' ' << std::get<2>(x) << '\n';
}

auto get() -> decltype(std::make_tuple(10, 11, 12)) {
    return std::make_tuple(10, 11, 12);
}

int main() {
    test(get());
}
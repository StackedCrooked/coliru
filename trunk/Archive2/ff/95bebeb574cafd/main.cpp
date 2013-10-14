#include <boost/iterator/function_input_iterator.hpp>
#include <cstdint>
#include <functional>
#include <iostream>
#include <vector>

std::function<std::uintmax_t()> fibonacci() {
    std::uintmax_t a = 0, b = 1;
    return [=] () mutable -> std::uintmax_t {
        std::uintmax_t old_a = a;
        a = b;
        b = old_a + a;
        return old_a;
    };
}

int main() {
    auto fib = fibonacci();
    auto begin = boost::make_function_input_iterator(fib, 0);
    auto end = boost::make_function_input_iterator(fib, 10);
    std::vector<std::uintmax_t> fibs(begin, end);
    for (auto&& fib : fibs) {
        std::cout << fib << '\n';
    }

    return 0;
}

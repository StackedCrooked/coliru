#include <boost/iterator/function_input_iterator.hpp>
#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <cstdint>

int main() {
    std::function<uintmax_t()> fib = [] {
        uintmax_t a = 0, b = 1, cur = a;
        return [=] () mutable { return (std::tie(cur, a, b) = std::make_tuple(a, b, a+b)), cur; };
    }();

    std::copy_n(
            boost::make_function_input_iterator(fib, 0), 10, 
            std::ostream_iterator<uintmax_t>(std::cout, "\n"));
}

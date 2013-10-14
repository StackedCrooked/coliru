#include <boost/iterator/function_input_iterator.hpp>

int main() {
    using namespace std;

    auto fib = [] () -> function<uintmax_t()> {
        uintmax_t a = 0, b = 1, cur = a;
        return [=] () mutable { return (tie(cur, a, b) = make_tuple(a, b, a+b)), cur; };
    }();

    std::copy_n(
            boost::make_function_input_iterator(fib, 0), 5, 
            std::ostream_iterator<uintmax_t>(std::cout, "\n"));

    std::copy(
            boost::make_function_input_iterator(fib, 0), { fib, 5 },
            std::ostream_iterator<uintmax_t>(std::cout, "\n"));
}


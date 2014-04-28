#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/iterator/function_input_iterator.hpp>

struct fib_impl {
    using result_type = int;
    int x = 0, y = 1;
    int operator()() {
        int result = x;
        x = y;
        y += result;
        return result;
    }
};

int main() {
    fib_impl f;
    std::copy(
        boost::make_function_input_iterator(f, 0),
        boost::make_function_input_iterator(f, 10),
        std::ostream_iterator<int>{std::cout, ", "}
    );  
}

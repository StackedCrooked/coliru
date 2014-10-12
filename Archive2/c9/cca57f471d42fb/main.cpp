#include <vector>
#include <functional>
#include <iostream>
#include <boost/iterator/function_input_iterator.hpp>

using boost::make_function_input_iterator;

struct generator {
  size_t i{0};
  typedef int result_type;
  result_type operator() () {
    return i++ % 3;
  }
};

int main() {
    generator f;
    auto begin = make_function_input_iterator(f, 0);
    auto end = make_function_input_iterator(f, 10);
    std::vector<int> v(begin, end);
    for (auto e : v)
      std::cout << e;
}

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>

class my_error : public std::runtime_error {
 public:
  explicit my_error(const std::string& e) : runtime_error(e) {}
};

template <class First>
std::string format(const First& first) {
    std::ostringstream stream;
    stream << first;
    return stream.str();
}

template <class First, class... Rest>
std::string format(const First& first, const Rest&... rest) {
    std::ostringstream stream;
    stream << first << format(rest...);
    return stream.str();
}

int main() {
  try {
    const int cols = 3;
    const int rows = 4;
    throw my_error(
      format("Number of columns in A (", cols, ") must match number of rows in B (", rows, ")"));
  }
  catch (const my_error &e) {
    std::cout << e.what() << "\n";
  }
  return 0;
}
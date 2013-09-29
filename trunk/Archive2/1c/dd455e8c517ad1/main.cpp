#include <iostream>
#include <type_traits>
#include <limits>

class MyInt {
};

class MyDouble {
};

namespace std {

template <>
struct numeric_limits<MyInt> {
  static const bool is_integer = true;
};

template <>
struct numeric_limits<MyDouble> {
  static const bool is_integer = false;
};

template <>
struct is_integral<MyDouble> {
  static const bool value = true;
};

} // namespace std

template <class T>
void test(const char* type) {
  std::cout << "-----" << std::endl;
  std::cout << type << std::endl;
  std::cout << "from numeric limits: ";
  std::cout << std::numeric_limits<T>::is_integer << std::endl;
  std::cout << "is integral: " << std::is_integral<T>::value << std::endl;
}

int main() {
  test<int>("int");
  test<double>("double");
  test<MyInt>("MyInt");
  test<MyDouble>("MyDouble");
}
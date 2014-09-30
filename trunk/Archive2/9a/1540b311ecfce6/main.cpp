#include <iostream>
#include <utility>
#include <type_traits>

struct foo {
  int    memfun1(int a) const { return a;   }
  double memfun2(double b) const { return b; }
};

int main() {
  std::result_of<decltype(&foo::memfun1)(foo, int)>::type i = 10;
  std::cout << i << std::endl;
  std::result_of<decltype(&foo::memfun2)(foo, double)>::type d = 12.9;
  std::cout << d << std::endl;
}

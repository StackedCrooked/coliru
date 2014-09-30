#include <iostream>
#include <utility>

struct foo {
  int    memfun1() const { return 1;   }
  double memfun2() const { return 2.0; }
};

int main() {
  decltype(std::declval<foo>().memfun1()) i = 10;
  std::cout << i << std::endl;
  decltype(std::declval<foo>().memfun2()) d = 12.9;
  std::cout << d << std::endl;
}
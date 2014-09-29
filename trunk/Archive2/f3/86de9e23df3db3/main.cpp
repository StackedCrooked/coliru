#include <iostream>
#include <utility>

struct foo {
  int    memfun1(int a) const { return a;   }
  double memfun2(double b) const { return b; }
};

int main() {
  decltype(std::declval<foo>().memfun1(1)) i = 10;
  std::cout << i << std::endl;
  decltype(std::declval<foo>().memfun2(10.0)) d = 12.9;
  std::cout << d << std::endl;
}
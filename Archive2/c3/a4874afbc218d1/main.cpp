#include <iostream>
#include <algorithm>

int main() {
  int foo[10];
  std::generate(foo, foo + 10, [i = 0]() mutable { return i++; });
  for (auto i : foo) {
    std::cout << i << std::endl;
  }
}
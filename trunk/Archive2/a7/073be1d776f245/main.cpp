#include <iostream>

class foo {
  int var = 99;
public:
  static int const i;
};

int const foo::i = [&] { return foo().var; }();

auto main() -> int {
  std::cout << foo::i << std::endl;
  return 0;
}
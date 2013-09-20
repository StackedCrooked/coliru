#include <utility>
#include <iostream>

template <int I, typename T>
struct foo;

template <std::size_t Index>
struct foo<Index, int*> {
  static int bar() {
    return 2;
  }
};

int main() {
  std::cout << foo<std::size_t(0), int*>::bar() << std::endl;
  std::cout << foo<0, int*>::bar() << std::endl;
}
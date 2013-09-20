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

template <int Index>
struct foo<Index, int*> {
  static int bar() {
    return 3;
  }
};

int main() {
  std::cout << foo<0, int*>::bar() << std::endl;
}
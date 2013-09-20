#include <utility>
#include <iostream>

template <int I, typename T>
struct foo;

enum Boo { BOO = 1 };

template <Boo boo>
struct foo<boo, int*> {
  static int bar() {
    return 2;
  }
};

int main() {
  std::cout << foo<BOO, int*>::bar() << std::endl;
}
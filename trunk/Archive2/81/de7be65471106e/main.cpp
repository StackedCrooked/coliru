#include <iostream>

auto g() {
  int i = 12;
  return [&] {
    i = 100;
    return i;
  };
}

void f() {
  int i = g()();
  std::cout << i;
}

int main() {
  f();
}
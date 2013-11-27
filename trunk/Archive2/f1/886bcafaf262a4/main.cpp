#include <iostream>

struct A {
 void fun() { std::cout << "fun \n"; };
};

int main() {
  A* a[2];

  // Pointer
  for (auto x : a) {
    x->fun();
  }
}

#include <iostream>
#include <functional>

struct A {
  explicit A(std::function<void()> f) { f(); }
};

struct B {
  void doit() {
    A([]() { std::cout << "hello" << std::endl; }
    return;
  }
};

int main() {
  B().doit();
}
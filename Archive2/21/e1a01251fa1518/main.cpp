#include <vector>
#include <memory>
#include <iostream>

struct Foo {
  int a;
  Foo(int in) : a(in) {}
};

int main() {
  auto foos = std::vector<std::unique_ptr<Foo>>(10);
  foos[5] = std::make_unique<Foo>(2);
  for (const auto& foo : foos) {
    if (foo)
      std::cout << foo->a << "\n";
  }
}

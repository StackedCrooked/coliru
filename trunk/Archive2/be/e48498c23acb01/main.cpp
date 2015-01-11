#include <atomic>
#include <iostream>

std::atomic<double> foo{0};

void add_to_foo(double bar) {
  auto current = foo.load();
  while (!foo.compare_exchange_weak(current, current + bar))
    ;
}

int main() {
  add_to_foo(1);
  add_to_foo(2);
  add_to_foo(3);
  std::cout << foo << '\n';
}

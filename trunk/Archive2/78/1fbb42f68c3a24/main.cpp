#include <initializer_list>
#include <iostream>

std::initializer_list<int> g() { return{ 1, 2, 3 }; }

void f() {
  auto I = g();
  for (auto V : I) std::cout << V << std::endl;
}

int main() { f(); }
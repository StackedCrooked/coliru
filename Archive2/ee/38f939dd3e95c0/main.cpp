#include <iostream>
#include <type_traits>

class Foo {
  ~Foo() {};
};

int main() {
  std::cout << std::boolalpha << std::is_destructible<Foo>::value << std::endl;
}
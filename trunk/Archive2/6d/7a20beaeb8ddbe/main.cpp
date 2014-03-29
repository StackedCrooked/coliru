#include <iostream>

int main() {
  int x = 42;
  const char* bob = "hello, world!";
  
  auto foo = [](auto&) {
    std::cout << "done" << std::endl;
  };
  
  foo(x);
  foo(bob);
}

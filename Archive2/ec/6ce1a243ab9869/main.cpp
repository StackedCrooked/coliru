#include <iostream>

struct Foo {
  void boo(const char*) {
    std::cout << "call: const char*" << std::endl;
  }
  
  void boo(char*) {
    std::cout << "call: char*" << std::endl;
  }
};

int main() {
  Foo foo;
  
  std::cout << "argument: char*" << std::endl;
  char* a = nullptr;
  foo.boo(a);
  
  std::cout << "argument: const char*" << std::endl;
  const char* b = "abc";
  foo.boo(b);
}
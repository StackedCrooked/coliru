#include <iostream>

class foo {
  static int count;
  int id;
public:
  foo() : id(++count) {}
  int getid() const { return id; }
};

int foo::count = 0;

int main() {
  foo f1, f2, f3;
  
  std::cout << f1.getid() << std::endl;
  std::cout << f2.getid() << std::endl;
  std::cout << f3.getid() << std::endl;
} 
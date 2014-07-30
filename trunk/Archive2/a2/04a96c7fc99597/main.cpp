#include <iostream>

struct base {
  virtual void foo(int) { std::cout << "base::foo(int)" << std::endl; }
  virtual void foo(char) { std::cout << "base::foo(char)" << std::endl; }
};

struct derived : public base {
  void foo(int) override { std::cout << "derived::foo(int)" << std::endl; }
};

int main(void) {
  derived d;
  base b;
  
  b.foo('1');
  d.foo('1');
}

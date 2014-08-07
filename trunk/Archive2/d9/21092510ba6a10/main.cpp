#include <iostream>

struct test{
      void f() const &{ std::cout << "lvalue object\n"; }
      void f() const &&{ std::cout << "rvalue object\n"; }
};

int main(){
  test tst;
  tst.f(); // lvalue, outputs "lvalue object\n"

  // make it a rvalue reference
  std::move(tst).f(); // rvalue, outputs "rvalue object\n"
}
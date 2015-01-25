#include <functional>
#include <iostream>

struct A { 
  operator int () const {
    std::cerr << "A::operator int\n";
    return 0;
  }
};

void func (int) {
  std::cerr << "func (int)\n";
}

int main () {
  auto x = std::bind (&func, A {});
  
  std::cerr << "+++\n";
  x (); 
  std::cerr << "+++\n";
}
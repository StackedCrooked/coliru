#include <iostream>

struct tricky {
  operator int() const { return 12; }    
};

struct base {
  void func(tricky &) { std::cout << "tricky" << std::endl; }
};

struct derived: base {
  void func(int) { std::cout << "int" << std::endl; }
};

int main(void) {
  derived d;
  tricky t;
  
  d.func(t);
}

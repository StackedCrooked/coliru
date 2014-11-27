#include <iostream>
struct X;
struct Y { operator X(); };

struct X { 
  X() { }
  X(const Y&) { std::cout << "Direct initialization" << '\n'; }
  X(const X&) { std::cout << "Copy ctor" << '\n'; }
};

Y::operator X() { std::cout << "Copy initialization" << '\n'; return X(); }

int main() { 
  Y y;
  X x = y;
}

#include <iostream>
struct B;
struct A { 
  operator B();
};

struct B { 
  B() { }
  B(A const&) { std::cout << "<direct> "; }
};

A::operator B() { std::cout << "<copy> "; return B(); }

int main() { 
  A a;
  B b1(a);  // 1)
  B b2 = a; // 2)
  (void)b1;
  (void)b2;
}
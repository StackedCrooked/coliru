#include <iostream>

struct A {
  virtual void p() { std::cout<<"A!\n"; }
};

struct B : A {
  void p() { std::cout<<"B!\n"; }
};

struct Param {
  enum {AA, BB} tag;
  union {
    A a;
    B b;
  };

  Param(const A &p)
#if test
    : tag(AA) {a=p;}
#else
    : tag(AA), a(p) {}
#endif

  A &get() { return tag == AA ? a : b; }
};

int main() {
  A a;
  a.p();
  Param u(a);
  A &ar = u.get();
  ar.p();
}
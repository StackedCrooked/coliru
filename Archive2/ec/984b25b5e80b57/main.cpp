#include <iostream>
#include <memory>
#include <mutex>

struct Obj {
  Obj () { std::cerr << "ctor\n"; }
 ~Obj() { std::cerr << "dtor\n"; }
};

void func () {
  Obj x;
  throw 123;
}

int main () {
  func ();
}
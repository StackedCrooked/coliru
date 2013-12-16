#include <iostream>

struct A {
  friend void func () { std::cerr << "A"; }
};

struct B {
  friend void func () { std::cerr << "B"; }
};

  // should error: undeclared identifier
  //    clang 3.3: compiles and executes func in B
  //    gcc 4.8.2: complains that func is defined twice

int
main (int argc, char *argv[])
{
  func ();
}
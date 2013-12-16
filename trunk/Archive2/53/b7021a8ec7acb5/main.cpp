#include <iostream>

struct Obj {
  void func () const {
    std::cerr << "func ";
  } 
};

struct A {
  Obj const* operator-> () const {
    return &obj;
  }

  Obj obj;
};

struct B {
  A operator-> () const {
    return a;
  }

  A a;
};

int
main (int argc, char *argv[])
{
  B b;

  b->func ();
}
#include <iostream>

struct Obj {
  static int i;
  Obj () {
    std::cerr << "ctor ";
  }

  ~Obj() {
    std::cerr << "dtor ";
    throw 123;
  }
};

int
main (int argc, char *argv[])
{
  try {
    Obj obj;
  } catch (...) {
    std::cerr << "exception ";
  }
}

#include <iostream>

struct Obj {
  static int i;
  Obj () : m (++i) {
    std::cerr << "ctor" << m << "\n";
  }

  ~Obj() {
    std::cerr << "dtor" << m << "\n";
    if (m == 5)
      throw 123;
  }
  int m;
};

int Obj::i = 0;

void f() {
    Obj asd[10]; (void)asd;
}

int
main (int argc, char *argv[])
{
  try {
    f();
  } catch (...) {
    std::cerr << "exception ";
  }
}
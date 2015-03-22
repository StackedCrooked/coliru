#include <iostream>
#include <ostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iterator>

#include <cstdlib>

class Foo;
class Boo { 
  Boo(Foo *foo) {
    foo->f();
  }
}

class Foo : public Boo {
  Foo() : Boo(this) {}
  void f() {}
}

int
main()
{
    Boo b;
    return EXIT_SUCCESS;
}

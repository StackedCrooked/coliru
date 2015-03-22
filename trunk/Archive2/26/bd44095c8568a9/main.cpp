#include <iostream>
#include <ostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iterator>

#include <cstdlib>

class Foo;
class Boo { 
    public :
  Boo(Foo *foo) {
    foo->f();
  }
};

class Foo : public Boo {
    public: 
  Foo() : Boo(this) {}
  void f() {}
};

int
main()
{
    Boo b(0);
    return EXIT_SUCCESS;
}

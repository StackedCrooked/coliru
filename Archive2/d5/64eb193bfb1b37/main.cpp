#include <iostream>

using namespace std;

struct S {
  S( ostream &os ) : os_( os ) { }
  ~S() { os_ << "The end.\n"; }         // line 7
  ostream &os_;
};

void f() {
  static S s( cout );
  (void)s;
}

int main() {
  f();
  return 0;
}
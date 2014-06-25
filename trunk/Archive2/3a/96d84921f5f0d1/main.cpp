#include <iostream>
#include <type_traits>

using std::cout;
using std::string;


class Base {
public:
  virtual void foo(int&) { cout << "int\n"; }
  virtual void fooForEnum(int&) { cout << "enum\n"; }
  virtual void foo(bool&) { cout << "bool\n"; }
  virtual void foo(string&) { cout << "string\n"; }
  
  template <class E>
  void foo(E& e, typename std::enable_if< std::is_enum<E>::value >::type *ignore=0) {
    int i = 0;
    fooForEnum(i);
    e = static_cast<E>(i);
  }
};

enum Ex { A, B};
struct NoEnum {};

int main()
{
  Ex ea = A;
  Base b;
  b.foo(ea);
  
  NoEnum ne;
  b.foo(ne);
}

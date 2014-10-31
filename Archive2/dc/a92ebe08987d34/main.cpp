#include <new>

bool foo() {
  union bar { int i; bool b; };
  union baz { char c; bar b; };
  auto b = baz{'x'};
  auto barptr = &b.b;
  auto boolptr = &barptr->b;
  new (boolptr) bool{true};
  return b.b.b;
}

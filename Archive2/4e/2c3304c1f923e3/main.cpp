#include <iostream>

struct Obj { int value; };

int main () {
  Obj  a = { 123 };
  int& r = a.value;

  auto f  = [r]{ return r; };

  r = 0;

  std::cout << f () << " " << a.value << "\n";
}
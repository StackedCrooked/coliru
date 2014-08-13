#include <iostream>

struct B {};

void f() {
  B b;
  B *b2 = new (&b) B;
  (void)b2;
}

int main() {
  f();
}
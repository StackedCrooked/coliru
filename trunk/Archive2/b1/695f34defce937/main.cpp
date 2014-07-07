#include <iostream>

using namespace std;

class A {
    int line;
public:
  A(int l):line(l) { cout << "a(" << line << ")" ; }
  ~A() { cout << "A(" << line << ")"; }
};

class B {
    int line;
public:
  B(int l):line(l) { cout << "b(" << line << ")" ; }
  ~B() { cout << "B(" << line << ")"; }
};

class C {
    int line;
public:
  C(int l):line(l) { cout << "c(" << line << ")" ; }
  ~C() { cout << "C(" << line << ")"; }
};

int i = 1;

B b(__LINE__);

int main() {
C c(__LINE__);
label:
  A a(__LINE__);
  B b(__LINE__);
  if (i--)
    goto label;
C c1(__LINE__);
}

#include <boost/bind.hpp>
#include <iostream>

struct X
{
  bool f(int a) {
    std::cout << a << "\n";
    return true;
  }
};

struct test {
  void f() { std::cout << "hi\n"; }
};

int main(int argc, const char *argv[])
{

  X x;
  int i = 5;
  bind(&X::f, &x, _1)(i);

  test t;
  //bind(&test::f, &t, _1)();

  return 0;
}

#include <iostream>
#include <utility>

using namespace std;

struct A {
  void method() & {
    cout << "method() &" << endl;
  }
  void method() && {
    cout << "method() &&" << endl;
  }
  void method() const & {
    cout << "method() const &" << endl;
  }
  void method() const && {
    cout << "method() const &&" << endl;
  }
};

struct B {
  void method1() & {
    cout << "method1()" << endl;
  }
  void method2() && {
    cout << "method2() &&" << endl;
  }
};

int main()
{
  A a1;
  a1.method();
  const A a2{};
  a2.method();
  A().method();
  const A a3{};
  std::move(a3).method();
}
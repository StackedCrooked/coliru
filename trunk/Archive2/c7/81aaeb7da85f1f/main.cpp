#include <iostream>

using namespace std;

template<typename T>
class A {
public:
    void foo() { cout << "Inside foo" << endl; }
    void bar() { cout << "Inside bar" << endl; }
};

#ifdef EXPLICIT_A_PLZ
  template class A<int>;
#endif

int main() {
  A<int> a;
  a.foo();
}
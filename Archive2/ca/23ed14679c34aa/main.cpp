#include <iostream>

using namespace std;

template<typename T>
class A {
public:
    void foo() { cout << "Inside foo" << endl; }
    void bar() { cout << "Inside bar" << endl; }
};

template class A<int>;   // <----

int main() {
  A<int> a;
  a.foo();
}
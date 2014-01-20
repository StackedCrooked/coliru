#include <iostream>

using namespace std;

template<typename T>
class A {
public:
    void foo() { cout << "Inside foo" << endl; }
    void
#ifdef EXPLICIT_A_PLZ
    __attribute__((used))
#endif
    bar() { cout << "Inside bar" << endl; }
};

int main() {
  A<int> a;
  a.foo();
}
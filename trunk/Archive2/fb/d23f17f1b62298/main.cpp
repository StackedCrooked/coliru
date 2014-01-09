#include <iostream>

template <class T, class U = T>
class A {
  public:
    void f();
};

template <class T>
class A<T, T> {
  public:
    void f();  // Unaltered method.

    // Some differences.
};

template <class T, class U>
void A<T, U>::f() { std::cout<< "Parametrized on T, U.\n"; }

template <typename T>
void A<T, T>::f() { std::cout << "Parametrized on T.\n"; }

int main() {
  A<int> a;
  a.f();
  A<int, float> b;
  b.f();
  return 0;
}
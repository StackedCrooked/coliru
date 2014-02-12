#include <iostream>

struct Base {
protected:
  void operator=(const Base&) { std::cout << "Called"; }
};

struct Derived : Base {
  void operator=(const Derived &) {}
  template<class Other>
  void operator=(const Other &) {}
};

struct X {};

int main() {
    Derived a;
    Derived b;
    X c;
    
    a = b;
    a = c;
}
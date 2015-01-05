#include <iostream>

class X 
{ 
public:
  X() : private_(123) { /*...*/ }

  template<class T>
  void f( const T& t ) { /*...*/ }

  int Value() { return private_; }

  // ...

private: 
  int private_; 
};

int main() {
    X x;
    std::cout << *reinterpret_cast<int*>(&x);
}
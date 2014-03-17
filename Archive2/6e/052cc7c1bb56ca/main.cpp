#include<iostream>

struct SomeClass {
  int nonVoidFunc() {
    std::cout << "nonVoidFunc()" << std::endl;
    return 0;
  }
  void voidFunc() {
    std::cout << "voidFunc()" << std::endl;
  }
};

class Proxy {
  SomeClass& sc;
  bool callVoid;
    
  Proxy(Proxy& p_sc) : sc(p_sc.sc), callVoid(false) { }
  Proxy& operator=(const Proxy& pr) { return *this;}
public:

  Proxy(SomeClass& p_sc) : sc(p_sc), callVoid(1) {}
  ~Proxy() {
    if ( callVoid) sc.voidFunc();          
  }

  template<typename T> operator T() {
    callVoid = false;
    return sc.nonVoidFunc();
  }

public:
  Proxy func() { return *this; }
};

int main() {
  SomeClass sc;
  Proxy p1(sc);

  int n = p1.func();  // prints nonVoidFunc()
  (void)n; 
  
  p1.func();   // prints voidFunc()
  return 0;
}
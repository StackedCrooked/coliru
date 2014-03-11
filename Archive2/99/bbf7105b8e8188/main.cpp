#include <iostream>

class A {
public:
   virtual void machin(int) {std::cout << "Pouet int" << std::endl;}
};

class B : public A {
public:
  virtual void machin(double) {std::cout << "Pouet double" << std::endl;}
private:
  //using A::machin;
};

int main() {
    
    A a;
    B b;
    
    a.machin(1);
    ((A*)&b)->machin(2);
    b.machin(3.0);
    
    return 0;
}
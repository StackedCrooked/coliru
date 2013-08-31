#include <iostream>

class A{
 private:
  int a;
 public:
 A() : a(0) {}
 virtual int getA() { return a ; }
  virtual void set();
};

class B : public A{
 private:
  int b;
 public:
  
  virtual void set();
};

void A::set(){ a=1;}

void B::set(){ b=1; A::set(); }

int main()
{
    B b1 ;
    
    b1.set() ;
    
    std::cout << b1.getA() << std::endl ;
}
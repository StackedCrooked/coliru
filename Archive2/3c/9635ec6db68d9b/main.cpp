#include <iostream>
 
class IA {
public:
  virtual void f1() = 0;
};

class IB : public IA {
public:
  virtual void f2() = 0;
};

class A : public IA {
public:
  void f1() {
    std::cout << "f1" << std::endl;
  }
};

class B :  public IB, public A
{
public:
  void f2() {
    std::cout << "f2" << std::endl;
  }
};

int main(int argc, char* argv[])
{
  B b;
  b.f1();
  b.f2();
  return 0;
}
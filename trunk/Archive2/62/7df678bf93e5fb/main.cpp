#include <iostream>
#include <typeinfo>

class Base
{
public:
 virtual void Teste()
 {
  std::cout << typeid(*this).name() << std::endl;
  (*this).Print();
 }
 
 virtual void Print()
 {
     std::cout << "Hello from Base" << std::endl;
 }
};

class Derived : public Base
{
public:
 virtual void Teste() override
 {
  std::cout << typeid(*this).name() << std::endl;
  Base::Teste();
 }
 
 virtual void Print() override
 {
     std::cout << "Hello from Derived" << std::endl;
 }
};

int main(int argc, char* argv [])
{
 Derived d;

 d.Teste();

 return 0;
}
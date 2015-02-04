#include <iostream>
#include <typeinfo>

class Base
{
public:
 virtual void Teste()
 {
  std::cout << typeid(this).name() << std::endl;
 }
};

class Derived : public Base
{
public:
 virtual void Teste() override
 {
  std::cout << typeid(this).name() << std::endl;
  Base::Teste();
 }
};

int main(int argc, char* argv [])
{
 Derived d;

 d.Teste();

 return 0;
}
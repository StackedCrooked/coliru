#include <iostream>
#include <cstdio>

class Foo
{
public:
   virtual void method1()
   {
      puts(__PRETTY_FUNCTION__);
      //std::cout << "A\n";
   }
   virtual void method2()
   {
      puts(__PRETTY_FUNCTION__);
      method1();
   }
};

class Fooo : public Foo
{
public:
   void method1()
   {
      puts(__PRETTY_FUNCTION__);
      //std::cout << "Z\n";
   }
   void method2()
   {
      puts(__PRETTY_FUNCTION__);
      method2();
   }
};

int main()
{
   Foo First, *Second;
   Fooo Third;
   Second = &Third;
   Third.method2();
   std::cout << "\n----------------\n\n";
   Second->method2();
}

#include <iostream>

struct Base
{
   virtual void foo() { std::cout << "Base::foo()\n"; }
   void bar() { foo(); }
};

struct Derived : Base
{
   virtual void foo() { std::cout << "Derived::foo()\n"; }
};

int main()
{
   Derived d;
   d.bar();
}
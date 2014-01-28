class Base
{
};

class A
{
public:
   A() { } // c'tor
   virtual ~A() { } // d'tor
   void FirstMethod();
   void SecondMethod();
};

class B : public A
{
public:
   B() { } // c'tor
   ~B() { } // d'tor
   void FirstMethod(); 
   void SecondMethod();
};

#include <iostream>
#include <typeinfo>

int main()
{
 A* aObject = new A();
 try {
 B* bObject= dynamic_cast<B*>(aObject);
 } catch(std::bad_cast& ex)
 {
     std::cout << ex.what();
 }
}
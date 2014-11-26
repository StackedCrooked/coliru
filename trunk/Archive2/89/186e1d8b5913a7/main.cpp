#include <iostream>

namespace N
{
   //define a class here
   struct A { void f() { std::cout << "N::A" << std::endl; }};
}

namespace M
{
   //define another class with same name!
   struct A { void f() { std::cout << "M::A" << std::endl; }};

   class B : public N::A  //NOTE : deriving from N::A
   {
      public:
         B()
         {
            A a;
            a.f(); //what should it print?
         }
   };
}

int main()
{
    M::B(); 
}
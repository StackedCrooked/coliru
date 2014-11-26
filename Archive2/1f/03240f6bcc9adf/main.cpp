#include <iostream>

namespace N
{
   //define a class here
   struct A 
   { 
       void f() { std::cout << "N::A" << std::endl; }
   };
}

namespace M
{
   //define another class with same name!
   struct A 
   { 
       void f() { std::cout << "M::A" << std::endl; }
   };

   struct B : N::A  //NOTE : deriving from N::A
   {
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
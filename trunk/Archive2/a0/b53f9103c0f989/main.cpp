#include <iostream>
struct X
{
   X() 
   {
       std::cout << "Hi\n";
   }
   ~X()
   {
       std::cout << "\nBye";
   }
} x;

int main()
{
   std::cout << "Hello";
}


#include <iostream>
#include <typeinfo>
 
int main()
{
   unsigned char c = 56;
   std::cout << typeid(c).name() << std::endl;
}
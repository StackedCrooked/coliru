#include <iostream>

int FuncWithoutReturn()
{
  int var = 10;
  ++var;
  // No return value here !!!
}

int main()
{
   int x ;
   
   std::cout << x << std::endl ;
    return 0;
}
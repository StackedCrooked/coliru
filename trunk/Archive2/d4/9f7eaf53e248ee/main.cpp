#include <iostream>

int main()
{
   int x = 0;
   const int *px = new (&x) const int(0);
   x = 1;
   std::cout << *px;  // 1?
}
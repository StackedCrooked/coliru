#include <iostream>

int main()
{
   int array[5] = { 77, 44, 33, 22, 11 };
   
   for (auto& v : array)
     std::cout << v << " ";
   std::cout << "\n";
}
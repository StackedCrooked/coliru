#include <iostream>
#include <string>
#include <cstring>
int main()
{
   char c1[] = { 'M', 'Y', ' ', 'P', 'R', 'O', 'F', 'E', 'S', 'S', 'I', 'O', 'N' };
   char c2[] = { 'M', 'Y', ' ', 'P', 'R', 'O', 'F', 'E', 'S', 'S', 'I', 'O', 'N','\0' };

   std::cout << "c1's size: " << sizeof c1 << " c2's size: "  << sizeof c2 << '\n'
             << "c2 also happens to be a C string, strlen(c2)=" << std::strlen(c2) << '\n';
}

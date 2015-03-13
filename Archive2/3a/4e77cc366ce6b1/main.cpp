#include <cstring>
#include <iostream>
 
int main()
{
   const char str[] = "How many characters does this string contain?";
 
   std::cout << "without null character: " << std::strlen(str) << '\n'
             << "with null character: " << sizeof str << '\n';
}
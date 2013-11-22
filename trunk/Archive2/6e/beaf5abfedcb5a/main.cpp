#include <cstring>
#include <iostream>
 
int main()
{
   const char str[] = "How many characters contains this string?";
 
   std::cout << "without null character: " << std::strlen(str) << '\n'
             << "with null characer: " << sizeof(str) << '\n';
}
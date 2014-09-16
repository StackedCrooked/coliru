#include <cstring>
#include <iostream>
 
int main()
{
   const char str[] = "How";
   const char* str2 = "Hell";
 
   std::cout << "without null character: " << std::strlen(str) << '\n'
             << "with null character: " << sizeof(str) << '\n';
             
    std::cout << std::strlen(str2) << std::endl << sizeof(str2) << std::endl;
}
#include <string>
#include <sstream>
#include <iostream>

int main()
{
   std::istringstream iss("1234.5678");
   
   int a, b;
   char c;
   
   iss >> a >> c >> b;
   
   std::cout << a << " " << c << " " << b;
   
   return 0;
}
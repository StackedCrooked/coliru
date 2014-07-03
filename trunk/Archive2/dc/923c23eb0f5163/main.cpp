#include <iostream>
#include <string>

int main()
{
   const std::string str = "12.3";
   // or `const char[] = {'1', '2', '.', '3', '\0'};

   const float var = std::stof(str);
   std::cout << var << '\n';
}

// $ myProgram
// 12.3
#include <iostream>
#include <string>
 
#if __cplusplus <= 201103L
  #error This application needs at least a C++11 compliant compiler
#endif

int main() 
{
    double f = 23.43;
    std::string f_str = std::to_string(f);
    std::cout << f_str << '\n';
}
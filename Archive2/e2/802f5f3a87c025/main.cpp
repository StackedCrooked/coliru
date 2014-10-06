#include <iostream>
#include <sstream>
 
int main()
{
    std::cout << "Hello, world" // the const char* overload
              << '\n';          // the char overload
//    std::string s = (std::ostringstream() << 1.2).str(); // rvalue overload
    std::cout << s << '\n';
}
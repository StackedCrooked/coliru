#include <iostream>
#include <sstream>
 
int main()
{
    std::cout << "Hello, world" // the const char* overload
              << '\n';          // the char overload
    auto& qq = std::ostringstream() << 5 << 7;
    qq << 5;
    std::cout << static_cast<std::ostringstream&>(qq).str();
}
#include <iostream>
#include <sstream>
 
int main()
{
    std::istringstream s("     this is a test");
    std::string line;
    getline(s >> std::ws, line);
    std::cout << "ws + getline returns: \"" << line << "\"\n";
}
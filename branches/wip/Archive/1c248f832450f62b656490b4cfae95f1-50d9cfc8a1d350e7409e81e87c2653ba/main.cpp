#include <iostream>
#include <sstream>
#include <string>
    
    
int main()
{   
    std::istringstream fake_cin("your mom is fat\nbut that never stopped me!");
    
    std::string line;
    while (std::getline(fake_cin, line))
    {
        std::cout << line << std::endl;
    }    
}

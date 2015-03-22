#include <iostream>

int main()
{
    std::string &x = std::string("Test");
    
    std::cout << x << std::endl;
    
    return 0;
}
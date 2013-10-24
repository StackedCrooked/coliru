#include <iostream>
#include <sstream>

int main()
{
    int val;
    const char *str = "-576";
    std::istringstream ss(str);
    ss >> val;
    std::cout << val << std::endl;
    
    return 0;
}
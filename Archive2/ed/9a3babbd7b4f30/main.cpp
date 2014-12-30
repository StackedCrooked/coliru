#include <iostream>
#include <string>

int main()
{
    //                        1         2         3         4         5         6         7
    //               1234567890123456789012345678901234567890123456789012345678901234567890
    std::string x = "1111111111111111111111111111111111111111111111111111111111111111111111";
    const char* b = x.substr(1, 64).c_str();
    std::cout << b << std::endl;
    std::string x2 = "999999999999999999999999999999999999999999999999999999999999999999999";
    std::cout << b << std::endl;
    //int p = std::atoi(b);
    
    return 0;
}

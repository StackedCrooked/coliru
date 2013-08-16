#include <iostream>
#include <string>
#include <functional>

int main()
{
    std::cout << std::hash<std::string>()("axl rose") << std::endl;
    std::cout << std::hash<std::string>()("oral sex") << std::endl;
}

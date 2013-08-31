#include <iostream>
#include <string>

int main()
{
    bool contains = std::string("").find(std::string("")) != std::string::npos;
    std::cout << "\"\" contains \"\": "
        << std::boolalpha << contains;
}

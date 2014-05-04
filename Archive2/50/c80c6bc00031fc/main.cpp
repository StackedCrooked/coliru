#include <iostream>
#include <sstream>

int main()
{
    std::stringstream ss("1 2 3 0XFF 4 5 6");
    unsigned value = 0;
    while (ss >> std::hex >> value) {
        std::cout << value << std::endl;
    }
}
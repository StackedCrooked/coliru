#include <iostream>
#include <sstream>

int main()
{
    std::stringstream ss("1 2 3 0xAB 4 5 6");
    int value = 0;
    while (ss >> value) {
        std::cout << value << std::endl;
    }
}
#include <iostream>
#include <exception>
#include <stdexcept>

int main()
{
    if(std::uncaught_exception()) {
        std::cout << "!\n";
    }
}
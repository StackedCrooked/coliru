#include <iostream>
#include <sstream>

int main()
{
    int value = 123;
    std::stringstream ss("Hello world!");

    ss >> value; // this will fail

    // will value still be guaranteed to be zero?
    std::cout << "value is " << value << std::endl;
}
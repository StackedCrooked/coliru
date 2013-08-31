#include <iostream>
#include <string>

int main()
{
    std::cout <<  std::stoi("8978xyz") << std::endl;
    std::cout <<  std::stol("8978xyz") << std::endl;
    std::cout <<  std::stoll("8978xyz") << std::endl;
}
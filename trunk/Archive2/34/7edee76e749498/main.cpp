#include <iostream>


int main()
{
    auto a = new int;
    auto b = new int;
    auto c = new int;
    
    std::cout << int(b - a) << std::endl;
    std::cout << int(c - b) << std::endl;
}
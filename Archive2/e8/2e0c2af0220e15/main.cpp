#include <iostream>

int main()
{
    int a = 0;
    int b = 0;
    int c = 0;
    
    [&](){a = 1;}();
    [=]()mutable {b = 1;}();
    [](int& input){input = 1;}(c);
    
    std::cout << "a = " << a << std::endl
              << "b = " << b << std::endl
              << "c = " << c << std::endl;
}
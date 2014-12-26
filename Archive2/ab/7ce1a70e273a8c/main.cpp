#include <iostream>

enum A{ x = -2, y = 2 };

int a = x;

int b = A::y; //OK, but it's not clear why?

int main()
{ 
    std::cout << b << std::endl; 
}
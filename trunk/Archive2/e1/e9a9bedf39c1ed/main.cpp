#include <iostream>
#include <string>

struct X
{
    X(int)
    {
        std::cout << "Constructor" << std::endl;
    }
    
    X(const X&)
    {
        std::cout << "Copy constructor" << std::endl;
    }
    
    X(X&&)
    {
        std::cout << "Move constructor" << std::endl;
    }
};

int main()
{
    X a(10); //constructor    
    X b(a); // copy
    X c(X(3)); //constructor, move
    
    (void)c;
    std::cout << std::endl;
}
#include <iostream>

class Noncopyable
{

public:
    Noncopyable(int = 0) { std::cout << "conversion!" << std::endl;}
    Noncopyable(Noncopyable const &) { std::cout << "copy constructor!" << std::endl; }
};

Noncopyable foo() { return 0; }

int main()
{
    foo();
    //Noncopyable a = 0;
    return 0;
}
#include <iostream>
#include <stdexcept>

struct Y
{
    Y() { throw std::exception{}; }
    ~Y() { std::cout << "Y::~Y()" << std::endl; }
    Y(int) : Y{} {  }
};

int main()
{    
    try
    {
        Y y{42};
    }
    catch (std::exception const&) { }
}
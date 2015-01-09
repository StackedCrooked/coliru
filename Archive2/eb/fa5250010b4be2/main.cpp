#include <iostream>
#include <ostream>

struct endlIfNotZero
{
    template <typename T>
    endlIfNotZero(const T& x) : endl(x != 0) {}
    
    const bool endl;
};

std::ostream& operator<<(std::ostream& out, const endlIfNotZero& e)
{
    if (e.endl)
        out << std::endl;
    return out;
}

int main()
{
    int x = 0;
    
    x = 0; std::cout << "Tal" << endlIfNotZero(x);
    x = 1; std::cout << "Tal" << endlIfNotZero(x);
    x = 2; std::cout << "Tal" << endlIfNotZero(x);
    x = 0; std::cout << "Tal" << endlIfNotZero(x);
    x = 1; std::cout << "Tal" << endlIfNotZero(x);
    x = 2; std::cout << "Tal" << endlIfNotZero(x);
}
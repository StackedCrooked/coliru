#include <iostream>
#include <type_traits>
#include <typeinfo>

struct X
{
    X() = default;
    X(X const&) { std::cout << "copy\n"; }
    X(X&&) { std::cout << "move\n"; }

    X& operator=(X)
    {
        return *this;
    }
};

int main() 
{
    X x, y;
    x = X{};
    x = y;
}
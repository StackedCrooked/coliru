#include <iostream>

struct X
{
    int x = 3;
    
    X()
    {
        std::cout << x << '\n';
        x = decltype(x)();
    }
};


int main()
{
    X x;
    std::cout << x.x;
}

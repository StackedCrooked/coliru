#include <iostream>

int main()
{
    int x = 0;
    const int& x_ref = x; 
    auto f = [&a=x_ref]() mutable
    {
        ++a;
        return a;
    };
    x = 1;
    std::cout << f() << '\n';
}
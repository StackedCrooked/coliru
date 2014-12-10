#include <stdexcept>
#include <iostream>


int x;


constexpr int c1(int n)
{
    return x = n;
}


int main()
{
    constexpr auto s = c1(0);
}

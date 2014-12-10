#include <stdexcept>
#include <iostream>


int x;


constexpr int c1(int n)
{
    return x = n;
}


int main()
{
    return c1(0);
}

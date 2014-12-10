#include <stdexcept>
#include <iostream>


constexpr int c1(int n)
{
    return printf("%d", n) + n;
}


constexpr int c2(int n)
{
    return rand() + n;
}


int main()
{
    c1(0);
    c2(0);
}

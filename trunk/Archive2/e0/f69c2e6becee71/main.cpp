#include <iostream>

int main()
{
    const int x = 0;
    *const_cast<int*>(&x) = 1;
    std::cout << x;
}
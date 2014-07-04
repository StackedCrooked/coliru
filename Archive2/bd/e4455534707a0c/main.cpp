#include <iostream>


int main()
{
    int&& x = 5;
    x = 6;
    std::cout << x << '\n';
}
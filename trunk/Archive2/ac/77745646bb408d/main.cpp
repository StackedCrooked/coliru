#include<iostream>

void operator>>(std::ostream const&, int) {}

int main()
{
    std::cin >> 2;
}
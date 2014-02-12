#include<iostream>

void operator>>(std::istream const&, int) {}

int main()
{
    std::cin >> 2;
}
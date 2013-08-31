#include <wheels/tuple.h++>
#include <tuple>

#include <iostream>

int main()
{
    std::tuple<char, double, short, int, char> standard;
    wheels::tuple<char, int, short, double, char> optimal;
    std::cout << "standard tuple has size " << sizeof(standard) << '\n';
    std::cout << "optimal tuple has size " << sizeof(optimal) << '\n';
}
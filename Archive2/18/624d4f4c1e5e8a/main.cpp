#include <iostream>

int main()
{
    double first = -1;
    double second = -2;

    std::cin >> first >> second;
    std::cout << std::fixed;
    if(first - second > 0 )
        std::cout << first << std::endl << second;
}
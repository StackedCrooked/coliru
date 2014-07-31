#include <iostream>

int main()
{
    double sum = 0.0;
    double temp = 0.0;
    while(std::cin >> temp)
    {
        sum += temp;
    }
    
    std::cout << sum << std::endl;
}
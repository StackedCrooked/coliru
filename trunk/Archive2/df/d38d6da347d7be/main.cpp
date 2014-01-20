#include <iostream>
#include <array>

template<typename T>
T n = T(5);

int main()
{
    n<int> = 10;
    std::cout << n<int> << " ";
    std::cout << n<double> << " ";
}

#include <iostream>
#include <iomanip>

int main()
{
    double d = 1000000000000000.0; // 10^16
    std::cout << std::fixed << d;
}

#include <iostream>
#include <iomanip>

int main()
{
    std::cout << std::setprecision(9) << std::fixed << (float)0.999999999 << '\n';
    // Output: 1.000000000
}
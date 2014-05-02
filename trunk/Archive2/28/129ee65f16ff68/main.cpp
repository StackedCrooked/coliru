#include <iostream>
#include <cmath>
double factorial(double arg)
{
    return std::tgamma(arg + 1);
}
int main()
{
    std::cout << "The factorial of 5 is " << factorial(5) << '\n'
              << "The factorial of 100 is " << factorial(100) << '\n';
}
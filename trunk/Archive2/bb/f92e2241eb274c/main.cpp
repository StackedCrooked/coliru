#include <iostream>

int main()
{
    double pi = 4.0;
    const int n = 1000000;
    int sign = -1;
    for(int i = 1; i <= n; ++i)
    {
        pi += 4.0 / (1 + 2.0*i)*sign;
        sign = -sign;
    }
    
    std::cout << pi << std::endl;
}
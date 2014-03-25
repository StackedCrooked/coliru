#include <iostream>
#include <cmath> //std::sqrt

int main()
{
    double pi = 0.0;
    const int n = 10000;
    
    for(int i = 1; i <= n; ++i)
    {
        pi += 1.0 / (i*i);
    }
    
    pi *= 6.0;
    pi = std::sqrt(pi);
    
    std::cout << pi << std::endl;
}
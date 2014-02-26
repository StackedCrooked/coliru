#include <iostream>
#include <cmath>

int main()
{
    long double x = 600851475143;
    long double n = 2;
    
    while (x > 1) {
        if (fmod(x,n) == 0) {
            x /= n;
            continue;
        }
        
        n++;
    }
    
    std::cout << n << '\n';
}
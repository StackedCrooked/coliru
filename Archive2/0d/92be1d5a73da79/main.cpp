#include <iostream>

int main()
{
    int n = 81;
    int pow = 2;
    while(pow << 1 < n)
    {
       pow <<= 1;
    }
    std::cout << pow << " is the largest power of 2 less than " << n << std::endl;
}
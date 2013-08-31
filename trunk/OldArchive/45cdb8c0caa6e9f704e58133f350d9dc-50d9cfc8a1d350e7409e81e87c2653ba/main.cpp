#include <iostream>

int& operator ""x12 (unsigned long long i)
{
    static int j = 42;

    return j;    
}

int main()
{
    std::cout << 0x12++ << std::endl;
}
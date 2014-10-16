#include <iostream>

unsigned char t[] = "ي";
unsigned char m0 = t[0];
unsigned char m1 = t[1];

int main()
{
    std::cout << t << std::endl;
    std::cout << (int)t[0] << std::endl;
    std::cout << (int)t[1] << std::endl;
    std::cout << m0 << std::endl;
    std::cout << m1 << std::endl;
}


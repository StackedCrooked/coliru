#include <iostream>
#include <string>

int main()
{
    unsigned char x = 150;
    unsigned char y = 229;
    
    int z = x - y;
    std::cout << z << '\n';
    std::cout << (x - y) << '\n';
    std::cout << (int)(unsigned char)(x - y) << '\n';
}

#include <iostream>
#include <bitset>
 
int main()
{
    std::bitset<8> b("01110010");
    std::cout << "initial value: " << b << '\n';
 
    while (b.any()) {
        while (!b.test(0)) {
            b >>= 1;
        }
        std::cout << b << '\n';
        b >>= 1;
    }
}
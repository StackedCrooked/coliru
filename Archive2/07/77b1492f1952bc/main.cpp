#include <iostream>
#include <bitset>
 
int main()
{
    for (unsigned long i = 0; i < 10; ++i) {
        std::bitset<5> b(i);
        std::bitset<5> b_inverted = ~b;
        std::cout << i << '\t';
        std::cout << b << '\t';
        std::cout << b_inverted << '\t';
        std::cout << b_inverted.to_ulong() << '\n'; 
    }
}
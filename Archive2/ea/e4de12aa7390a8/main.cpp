unsigned short add(unsigned short a, unsigned short b)
{
    unsigned short carry = a & b;
    unsigned short result = a ^ b;
    while(carry != 0)
    {
        unsigned short shiftedcarry = carry << 1;
        carry = result & shiftedcarry;
        result ^= shiftedcarry;
    }
    return result;
}

#include <iostream>
int main() {
    for(int x=0; x<11; ++x) {
        for(int y=0; y<11; ++y) {
            int z = add(x,y);
            std::cout<<x<<'+'<<y<<'='<<z<<(z==x+y?"\n":" fail\n");
        }
    }
}
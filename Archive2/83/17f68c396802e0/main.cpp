#include <iostream>

void test(unsigned Number, unsigned Mask)
{
    if (((Mask&0xF000)!=0xF000 && (Mask&0xF000)!=(Number&0xF000)) ||
        ((Mask&0x0F00)!=0x0F00 && (Mask&0x0F00)!=(Number&0x0F00)) ||
        ((Mask&0x00F0)!=0x00F0 && (Mask&0x00F0)!=(Number&0x00F0)) ||
        ((Mask&0x00F0)!=0x000F && (Mask&0x000F)!=(Number&0x000F)))
    {
        std::cout << "fail\n";
    } else {
        std::cout << "pass\n";
    }
}



int main() {
    unsigned Mask = 0xF7F7;
    test(0xFFFF, Mask); 
    test(0xF0F0, Mask); 
    test(0x0000, Mask); 
    test(0xF7F0, Mask);
    test(0x0700, Mask);
    test(0xF0F7, Mask);
    test(0x0007, Mask);
    test(0xF7F7, Mask);
    test(0x0707, Mask);
}
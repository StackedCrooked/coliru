#include <iostream>

typedef unsigned int ullong;

int main() {
    std::cout << std::hex;
    int myInteger = 0x12345678;
    
    int drop_for_high = 16;
    unsigned high = (unsigned)myInteger >> drop_for_high;
    
    int drop_for_low = 16;
    unsigned low = (unsigned)myInteger << drop_for_low >> drop_for_low;    
    
    std::cout << high << ' '  << low;
}
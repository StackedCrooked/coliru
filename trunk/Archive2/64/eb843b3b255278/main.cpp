#include <iostream>

typedef unsigned int ullong;

int main() {
    std::cout << std::hex;
    int myInteger = 0x1234;
    
    int drop_for_high = 8;
    int high = (unsigned)myInteger >> drop_for_high;
    
    int drop_for_low = 24;
    int low = (unsigned)myInteger << drop_for_low >> drop_for_low;    
    
    std::cout << high << ' '  << low;
}
#include <iostream>

int main() {
    signed char b = 0;
    //       0 0 0 0 0 0 0 0
    //       7 6 5 4 3 2 1 0
    
    b |= (1 << 7);
    
    switch(b) {
    case -128:
        std::cout << "10000000\n";
        break;
    case 64:
        std::cout << "0100000\n";
        break;
    // etc
    default:
        std::cout << "...";
        break;
    };
}
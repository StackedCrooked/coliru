#include <iostream>
#include <algorithm>
#include <vector>      

int main() {
    int a = -4;
    unsigned int b = -a;
    std::cout << (b == a) << std::endl; // writes 1, Ok
    
    char c = -4;
    unsigned char d = -c;
    std::cout << (d == c) << std::endl; // writes 0
}
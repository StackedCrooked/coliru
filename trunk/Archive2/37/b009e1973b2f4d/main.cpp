#include <iomanip>
#include <iostream>
#include <cstdio>

int main() {
    std::cout << std::setfill(' ')
              << std::setw(10) 
              << std::setfill('0')
              << std::setw(6)
              << 3;
    printf("\n%10.6d", 3);
}
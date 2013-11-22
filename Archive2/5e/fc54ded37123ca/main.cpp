#include <iostream>
#include <random>

#include <math.h>


int main() {
    
    
    int pos = 10 % 3;
    int pos2 = 10 % -3;
    int neg = -10 % 3;
    int neg2 = -10 % -3;
    
    std::cout << pos << std::endl;
    std::cout << pos2 << std::endl;
    std::cout << neg << std::endl;
    std::cout << neg2 << std::endl;
}
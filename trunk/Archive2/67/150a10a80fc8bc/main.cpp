#include <iostream>
 
int main() {
    int x = 2;
    int y = 5;
    
    //x ^= y ^= x ^= y;
    x = x ^ (y = y ^ (x = (x ^ y)));

    std::cout << "x=" << x << " y=" << y << std::endl;
}
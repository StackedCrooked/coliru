#include <iostream>

int main() {
    int a = 2;
    int b = 3;
    double x = (a + b) >> 1;
    double y = (a + b) / 2.0;
    
    std::cout << (x == y) << '\n';
}
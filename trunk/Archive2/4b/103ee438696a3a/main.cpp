#include <iostream>

int main(){
    double x = 0.123;
    int y = 123;
    std::cout << static_cast<int>(x) << '\n';
    std::cout << static_cast<double>(y) << '\n';
}
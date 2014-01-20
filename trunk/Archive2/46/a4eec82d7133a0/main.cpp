#include <string>
#include <iostream>

int main() {
    int    int1    = 0;
    double double1 = 0;
    float  float1  = 0;
    
    const std::string str = "words" + std::to_string(int1) + std::to_string(double1) + std::to_string(float1);
    std::cout << str << '\n';
}
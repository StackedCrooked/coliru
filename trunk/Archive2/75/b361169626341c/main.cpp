#include <iostream>

int main() {
    long long temp  = 0x24924925;
    long long temp1= 0xf4240;
    long long multiply = temp * temp1;
    std::cout << std::hex << multiply;
}
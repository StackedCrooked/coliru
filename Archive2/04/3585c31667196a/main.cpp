#include <iostream>
#include <algorithm>
    
int add(int a, int b, int c) {
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    return a + b + c;
}

int main() {
    auto add1 = std::bind(add, 1, std::placeholders::_2, std::placeholders::_1);
    std::cout << "a + b + c = " << add1(2,42) << std::endl;
}
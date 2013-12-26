#include <initializer_list> 
#include <iostream>

struct T {
    T() {std::cout << "default\n";}
    T(std::initializer_list<int>) {std::cout << "init list\n";}
};

int main() {
    T{};   
}
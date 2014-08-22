#include <cmath>
#include <iostream>

struct A {
    bool b{false};
};


int main() {
    A a1;
    a1.b = true;
    A a2 = a1;
    std::cout << std::boolalpha << a2.b << std::endl; 
}
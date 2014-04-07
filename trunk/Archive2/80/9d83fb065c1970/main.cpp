#include <iostream>

struct X {
    int a;
    char b;
};

int main() {
    X x;
    
    std::cout << &(x.a) << std::endl;
    std::cout << &(x.b) << std::endl;
}
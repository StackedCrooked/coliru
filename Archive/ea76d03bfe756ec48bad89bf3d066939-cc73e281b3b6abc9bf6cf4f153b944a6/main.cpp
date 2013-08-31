#include <iostream>
#include <string>
#include <sstream>

struct A {
    operator int() {return 0;}
    operator float() {return 0;}
};

int main() {
    std::cout << A();
}
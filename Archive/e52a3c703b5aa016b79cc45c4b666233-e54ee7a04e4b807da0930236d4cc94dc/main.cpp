#include <iostream>

int f1() {std::cout << "f1\n"; return 0;}
int f2() {std::cout << "f2\n"; return 0;}

int main() {
    std::cout << f1() << f2();
}
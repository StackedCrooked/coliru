#include <iostream>

struct S {
    S(int) {std::cout << "S(int)\n";}
    S(const S &) {std::cout << "S(const S &)\n";}
    ~S() {std::cout << "~S()\n";}
};

int main() {
    S s = 2;
}
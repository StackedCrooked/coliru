#include <iostream>

struct S {
    S() {std::cout << "S()\n";}
};

int main() {
    S arr[2]{};
}
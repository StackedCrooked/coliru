#include <iostream>

struct S {
    S() : i{} {std::cout << i << ' ' << j;}
    int i;
    int j;
};

int main() {
    S s[1] = {};
}
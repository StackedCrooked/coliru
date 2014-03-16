#include <iostream>

struct S {
    S() : parent(this) {std::cout << parent << '\n';}
    S *parent;  
};

int main() {
    S s;
    S s2;
    S *p = new(&s2) S;
}
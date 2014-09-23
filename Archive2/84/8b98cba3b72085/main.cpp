#include <iostream>

void f(int x) {std::cout << "in f " << x << std::endl;}

typedef void (*pf)(int);

int main() {
    pf funcs[1];
    funcs[0] = &f;
    (funcs[0])(42);
}
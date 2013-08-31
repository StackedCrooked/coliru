#include <iostream>

int main() {
    int***** p = new int****;
    *p = new int***;
    **p = new int**;
    ***p = new int*;
    ****p = new int(42);
    std::cout << *****p << '\n';
    return 0;
}

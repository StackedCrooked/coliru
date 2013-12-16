#include <iostream>
int main() {
    int xs[10];
    int* p = xs;
    p += true + 42;

    std::cout << p << std::endl;
    return 0;
}

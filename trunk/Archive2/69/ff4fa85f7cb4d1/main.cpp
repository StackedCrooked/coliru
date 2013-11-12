#include <iostream>

void p(int x[]) {
    std::cout << sizeof(x) << std::endl;
}

int main() {
    int y[] = { 1, 2, 3, 4, 5, 6 };
    std::cout << sizeof(y) << std::endl;
    p(y);
}
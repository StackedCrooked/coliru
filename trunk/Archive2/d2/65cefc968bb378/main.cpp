#include <iostream>

void advance(char const *&ptr) {
    ++ptr;
}

int main() {
    char const *str = "Hello";
    advance(str);
    std::cout << str;
    return 0;
}

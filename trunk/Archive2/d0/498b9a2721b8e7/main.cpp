#include <cstring>
#include <iostream>
int main() {
    bool a;
    memset(&a, 0x03, sizeof(bool));
    if (a) {
        std::cout << "a is true!" << std::endl;
    }
    if (!a) {
        std::cout << "!a is true!" << std::endl;
    }
}
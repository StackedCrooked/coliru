#include <iostream>

int main() {
    auto *p = new int;
    std::cout << p;
    delete p;
}
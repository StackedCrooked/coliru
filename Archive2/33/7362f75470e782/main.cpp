#include <iostream>

void x() {
    std::cout << "x!\n";
}

int main() {
    auto& y = x;
    x();
    y();
}
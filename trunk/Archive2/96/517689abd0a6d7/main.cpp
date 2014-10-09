#include <iostream>

int main() {
    const int x = 5;
    const_cast<int&>(x) = 9;
    std::cout << x;
}
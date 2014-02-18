#include <iostream>

int f(const int);

int f(int i) { return i + 1; } // The builds normally even when this definition
                               // is in a different source file


int main() {
    std::cout << f(3) << '\n';
}
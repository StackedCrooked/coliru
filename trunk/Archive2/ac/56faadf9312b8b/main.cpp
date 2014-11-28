#include <iostream>

int foo() {
}

int main() {
    std::cout << "UB " << foo() << "!\n";
}
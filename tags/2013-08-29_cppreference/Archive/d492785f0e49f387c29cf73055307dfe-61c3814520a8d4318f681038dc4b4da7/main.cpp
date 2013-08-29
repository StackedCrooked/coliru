#include <iostream>

void f(int const);
void f(int) {
    std::cout << "Hmm";
}

int main() {
    int const x = 42;
    f(x);
}

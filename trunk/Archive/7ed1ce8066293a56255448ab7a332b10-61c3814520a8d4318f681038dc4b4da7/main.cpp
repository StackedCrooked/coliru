#include <iostream>

void f(int const x);
void f(int x) {
    x = 17;
    std::cout << "Hmm";
}

int main() {
    int const x = 42;
    f(x);
}

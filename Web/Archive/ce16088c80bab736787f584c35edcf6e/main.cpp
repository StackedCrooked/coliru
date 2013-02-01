#include <iostream>
int main() {
    int i = 42;
    [&i](int i) { std::cout << i; }(0);
}
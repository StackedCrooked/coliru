#include <iostream>
struct A {
    static const int a = 5;
    A() { std::cout << &a; }
};
int main() {
    A d_A;
    return 0;
}

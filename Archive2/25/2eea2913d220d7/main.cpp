#include <iostream>
struct A {
protected:
    void hidden() { std::cout << "But I was hidden !?\n"; }
};
struct B : A {
    using A::hidden;
};
int main() {
    B().hidden();
}
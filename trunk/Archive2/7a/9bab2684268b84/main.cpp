#include <iostream>

struct Test {
    Test() { std::cout << "ctor\n"; }
    Test(const Test &) { std::cout << "copy\n"; }
};

int main() {
    Test t = Test();
}

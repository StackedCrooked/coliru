#include <iostream>

class C {
    int x = 42;
public:
    void f() { std::cout << x << std::endl; }
};

int main() {
    C().f();
}
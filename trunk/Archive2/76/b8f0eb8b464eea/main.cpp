#include <iostream>

struct test {
    void f() {
        std::cout << "f\n";
    }

    decltype(f) g = f; // ?
};

int main() {
    test x;
    x.f();
}

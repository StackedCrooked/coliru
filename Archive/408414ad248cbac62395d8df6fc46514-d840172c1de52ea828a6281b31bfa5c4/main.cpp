#include <iostream>

class A {
public:
    int a;
    A(): a(100) {}
    auto operator*(size_t n) -> decltype(*this) {
        a *= n;
        return *this;
    }
};

int main() {
    A a;
    a * 4;
    std::cout << a.a;
}
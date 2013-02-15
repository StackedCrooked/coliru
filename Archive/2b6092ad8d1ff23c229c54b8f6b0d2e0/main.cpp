#include <iostream>

struct A {
    int a = 10;
    int b = 20;
    friend std::ostream& operator<<(std::ostream& out, const A& a) {
        out << a.a << '\n' << a.b;
        return out;
    }
};

int main() {
    A aa;
    std::cout << aa;
}
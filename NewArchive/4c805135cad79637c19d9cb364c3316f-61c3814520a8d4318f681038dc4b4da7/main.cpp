#include <iostream>

class A {
public:
    int a = 100;
    int b = 200;
    int c = 300;
    friend std::ostream& operator<<(std::ostream& out, const A& a) {
        out << a.a << ' ' << a.b << ' ' << a.c << '\n';
        return out;
    }
};

int main() {
    A a;
    std::cout << a;
}
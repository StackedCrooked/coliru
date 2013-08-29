#include <iostream>

class Test {
public:
    int a = 100;
    int b = 20;
    int c = 300;
    Test() = default;
    Test(int bb): b(bb) {}
};

class Two {
public:
    Test test{200};
    int d = 400;
    Two() = default;
    friend std::ostream& operator<<(std::ostream& out, const Two& t) {
        out << "(" << t.test.a << ", " << t.test.b << ", " << t.test.c << ", " << t.d << ")";
        return out;
    }
};

int main() {
    Two t;
    std::cout << t;
}


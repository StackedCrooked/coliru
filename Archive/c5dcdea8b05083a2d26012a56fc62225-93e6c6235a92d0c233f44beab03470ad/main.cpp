#include <iostream>

class A {
public:
    enum Lol {
        one = 1, two, three
    };
    static bool overOne(Lol lol) {
        return lol > Lol::one;
    }
};

int main() {
    A a;
    if(a.overOne(A::two)) {
        std::cout << "...";
    }
    if(A::overOne(A::three)) {
        std::cout << "\n....";
    }
}
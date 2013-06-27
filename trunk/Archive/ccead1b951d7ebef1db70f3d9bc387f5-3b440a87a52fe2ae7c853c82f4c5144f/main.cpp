#include <iostream>

class A {
    int info{};
    friend std::ostream& operator<<(std::ostream& os, const A& a);
};

class B {
    A member_a;
    friend std::ostream& operator<<(std::ostream& os, const B& b);
};

std::ostream& operator<<(std::ostream& os, const A& a) {
    os << a.info;
    return os;
}

std::ostream& operator<<(std::ostream& os, const B& b) {
    os << b.member_a;
    return os;
}


int main() {
    B b;
    std::cout << b;
}
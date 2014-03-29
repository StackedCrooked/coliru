struct A {};
struct B {};
struct Proxy {};

Proxy operator==(const A& a, const B& b) {
    return {};
}

bool operator==(const Proxy& p, const B& b) {
    return true;
}

bool operator==(const Proxy& p, const A& a) {
    return true;
}


#include <iostream>

int main() {
    A a;
    B b;
    if(a == b == a) {
        std::cout << "Bad.\n";
    }
}
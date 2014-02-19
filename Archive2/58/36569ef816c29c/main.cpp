#include <iostream>

struct foo {
    foo() : count(counter++) { std::cout << "[foo(" << count << ")]"; }
    ~foo() { std::cout << "[~foo(" << count << ")]"; }

    int count;
    static int counter;
};

int foo::counter;

std::ostream& operator <<(std::ostream& out, foo const& foo) {
    return out << "[<<foo:" << foo.count << "]";
}

int main() {
    std::cout << foo() << foo() << '\n';
}
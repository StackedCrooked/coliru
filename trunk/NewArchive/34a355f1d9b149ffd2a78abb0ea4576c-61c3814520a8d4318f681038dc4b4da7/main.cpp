#include <memory>
#include <iostream>

struct cl {
    int x;
    int& y() { return x; }
};

void foo(int&) {
    std::cout << "&\n";
}
void foo(int&&) {
    std::cout << "&&\n";
}

cl rval() {
    return { 0 };
}

int main() {
    foo(rval().x);
    foo(rval().y());
}
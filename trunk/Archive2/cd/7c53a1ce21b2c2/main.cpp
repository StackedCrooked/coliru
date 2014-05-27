#include <vector>
#include <iostream>

struct foo {
    int x;
    foo(int x) : x(x) {}
    ~foo() { std::cout << "foo"; }
};
struct S {
    foo&&  f;
};

int main() {
    S s1{foo(1)}; // construct with temporary
    std::cout << "bar";
    std::cout << s1.f.x;
    return 0;
}
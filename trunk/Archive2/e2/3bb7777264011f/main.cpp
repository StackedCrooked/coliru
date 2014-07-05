#include <iostream>

struct ProvideFoo {
    void foo() { std::cout << "foo\n"; }
};

struct ProvideBar {
    void bar() { std::cout << "bar\n"; }
};

struct Concrete : public ProvideFoo, public ProvideBar {};

int main() {
    Concrete c;
    c.foo();
    c.bar();
}

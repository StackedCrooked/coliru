#include <iostream>

struct AbsBase {
    virtual void foo() = 0;
    virtual void bar() = 0;
};

struct ProvideFoo: virtual AbsBase {
    void foo() { std::cout << "foo\n"; }
};

struct ProvideBar: virtual AbsBase {
    void bar() { std::cout << "bar\n"; }
};

struct Concrete : public ProvideFoo, public ProvideBar {};

int main() {
    Concrete c;
    c.foo();
    c.bar();
}

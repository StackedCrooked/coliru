#include <iostream>

struct AbsFoo {
    virtual void foo() = 0;
};

struct AbsBar {
    virtual void bar() = 0;
};

struct ProvideFoo: AbsFoo {
    void foo() { std::cout << "foo\n"; }
};

struct ProvideBar: AbsBar {
    void bar() { std::cout << "bar\n"; }
};

struct Concrete : public ProvideFoo, public ProvideBar {};

int main() {
    Concrete c;
    c.foo();
    c.bar();
}

#include <iostream>

struct ProvideFoo {
    void foo() { std::cout << "foo\n"; }
};

struct ProvideBar {
    void bar() { std::cout << "bar\n"; }
};

struct Concrete : public ProvideFoo, public ProvideBar {
    // I guess I could put function wrappers here... sigh...
    //void bar() {ProvideBar::bar();}
    //void foo() {ProvideFoo::foo();}
};

int main() {
    Concrete c;
    c.foo();
    c.bar();
}

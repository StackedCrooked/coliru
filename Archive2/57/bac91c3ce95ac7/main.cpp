#include <iostream>

struct Foo {
    virtual void do_it() = 0;
};

struct Bar : Foo {
    void do_it() {
        std::cout << "Bar is doing it!\n";
    }
};

struct Baz : Foo {
    void do_it() {
        std::cout << "Baz is doing it!\n";
    }
};

void do_it(Foo &foo) {
    foo.do_it();
}

int main() {
    Bar bar;
    Baz baz;
    do_it(bar);
    do_it(baz);
}

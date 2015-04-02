#include <iostream>

struct foo;

struct bar {
    void (foo::* ptr)();
    
    void
    something(foo&);
};

struct foo {
    void
    react() {
        std::cout << "I'm reacting to something\n";
    }
};

void
bar::something(foo& f) {
    (f.*ptr)();
}

int
main() {
    bar b{&foo::react};
    foo f;
    b.something(f);
}

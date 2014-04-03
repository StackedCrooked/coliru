#include <utility>

struct Foo {
    Foo() {}
    Foo(Foo&&) {}
    Foo(const Foo&) = delete;
    Foo& operator=(const Foo&) = delete;
};


Foo f() {
    Foo foo;
    return foo;
}

int main() {
    Foo foo = f();
}
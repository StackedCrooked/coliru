#include <utility>

struct Foo {
    Foo() = default;
    Foo(Foo&&) = default;
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
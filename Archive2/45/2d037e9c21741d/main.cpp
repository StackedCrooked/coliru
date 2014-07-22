#include <cassert>

struct Foo {
    Foo(int bar) : bar_(bar) {}
    Foo(const Foo&) = delete;
    Foo(Foo&&) = default;
    static Foo Create() {
        Foo foo(42);
        return foo;
    }
    int bar_;
};

int main() {
    Foo foo = Foo::Create();
    assert(foo.bar_ == 42);
}

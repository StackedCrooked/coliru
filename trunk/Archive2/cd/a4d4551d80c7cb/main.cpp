struct Foo {
    Foo() {}
    Foo(const Foo&) = delete;
    Foo(Foo&&) {}
};

Foo make_foo()
{
    const volatile Foo x;    // any CV qualifier is acceptable
    return x;                // may use Foo::Foo(Foo &&)
}

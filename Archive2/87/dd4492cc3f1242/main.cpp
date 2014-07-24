struct Foo_class {};
using Foo = Foo_class const;

Foo FuncBar()
{
    return Foo();
}

auto main() -> int
{
    // some where else
    Foo &myFoo = FuncBar();
    (void) myFoo;
}

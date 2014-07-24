struct Foo_class {};
using Foo = Foo_class&;

Foo FuncBar()
{
    static Foo_class the_foo;
    return the_foo;
}

auto main() -> int
{
    // some where else
    Foo &myFoo = FuncBar();
    (void) myFoo;
}

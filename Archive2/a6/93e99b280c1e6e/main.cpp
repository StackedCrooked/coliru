class Foo{};
class Bar{};
int main()
{
    Foo foo;
    auto foo = Foo();       // <- error C2086: 'Foo foo' : redefinition
    ////////////
    Bar* boo = new Bar();
    auto boo = new Bar();   // <- error C2040: 'boo' : 'auto' differs in levels of indirection from 'Bar *'

    return 0;
}
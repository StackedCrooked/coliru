struct Foo
{
    Foo() {}
    Foo( Foo && );
    Foo( const Foo & ) = delete;
};

Foo GetFoo()
{
    return Foo();
}

int main()
{
    Foo f = GetFoo();
}
struct Foo
{
    static const char str[];
};

const char Foo::str[] = "test";

int main()
{
    Foo foo;
    (void)foo;
}

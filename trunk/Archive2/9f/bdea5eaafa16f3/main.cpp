struct foo
{
    struct bar {};
    friend void meow(foo) { bar x; (void)x; }
};

int main()
{
    meow( foo{} );
}
struct foo
{
    friend void meow(foo) { bar x; (void)x; }
    struct bar {};
};

int main()
{
    meow( foo{} );
}
struct foo
{
    foo() = default;
    explicit foo(foo const&) {}
};

int main()
{
    foo x(foo{});
    foo y = foo();
}
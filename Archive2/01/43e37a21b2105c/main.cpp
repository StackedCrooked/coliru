struct foo
{
    foo() = default;
    explicit foo(foo const&) {}
};

int main()
{
    foo x;
    auto y(x);
    auto z = x;
}
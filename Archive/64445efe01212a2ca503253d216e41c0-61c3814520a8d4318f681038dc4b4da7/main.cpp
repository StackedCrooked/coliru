
struct foo {
    foo(const int n);
};

foo::foo(int n)
{
    n = 1;
}

int main()
{
    foo f{3};
}
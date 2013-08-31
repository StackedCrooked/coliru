
struct foo {
    foo(int n);
};

foo::foo(const int n)
{
    n = 1;
}

int main()
{
    foo f{3};
}
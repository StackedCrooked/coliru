struct Foo
{
    int a;
};

template<typename T>
void test(T x)
{
    [&](auto)
    {
        x.a;
    };
}

int main()
{
    test(Foo{0});
    test(0);
}
struct foo
{
    int m;
};

int main()
{
    constexpr auto bar0 = foo();
    constexpr foo bar1;
}
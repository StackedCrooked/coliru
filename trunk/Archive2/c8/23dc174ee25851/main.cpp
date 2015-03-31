struct foo {
    static constexpr auto bar = 0;
};

constexpr decltype( foo::bar ) foo::bar;

int main()
{
    return foo::bar;
}
struct C
{
    auto
    f(int) const &
    {}

    auto
    f(int) &
    {}

    auto
    f(int) &&
    {}
};

int main()
{
#if 1
    C{}.f(1);
#endif
#if 1
    C c;
    c.f(1);
#endif
}

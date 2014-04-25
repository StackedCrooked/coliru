struct C
{

    template< typename X >
    auto
    f(X &&) const &
    { ; }

    template< typename X >
    auto
    f(X &&) &
    { ; }

    template< typename X >
    auto
    f(X &&) &&
    { ; }

};

int main()
{
    int i{};
#if 1
    C{}.f(i);
#endif
#if 1
    C c{};
    c.f(i);
#endif
    return 0;
}

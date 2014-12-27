template<typename>
struct B
{
    typedef int Type;
};

template<typename U>
static U f(U u);

template<typename T>
struct A
{
    template<typename U>
    static U f(U u);

    B<decltype(f(0))>::Type m1; // typename required
};
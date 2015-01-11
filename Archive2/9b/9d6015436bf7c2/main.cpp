struct foo
{
    constexpr static int bar = 42;
};

template<typename T>
constexpr T const& max(T const& p0, T const& p1)
{
    if(p1 < p0) return p0;
    return p1;
}

int main()
{
    constexpr auto x = max(foo::bar, foo::bar);
}
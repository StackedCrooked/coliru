union A { int x; char c; };

constexpr bool f()
{
    return A{1}.c == 1;
}

static_assert(f(), "1x");
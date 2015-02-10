template <class F>
constexpr auto indirect(F f) -> decltype(f()) {
    return f();
}

constexpr int f()
{
    return 1;
}

constexpr int foo = indirect(f);

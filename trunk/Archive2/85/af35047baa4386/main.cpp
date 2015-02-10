template <class F>
constexpr auto indirect(F f) -> decltype(f()) {
    return f();
}

template <class F>
constexpr auto really_indirect(F f) -> decltype(indirect(f)) {
    return indirect(f);
}

constexpr int f()
{
    return 1;
}

constexpr int foo = indirect(f);
constexpr int bar = really_indirect(f);

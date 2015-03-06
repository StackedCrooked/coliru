#include <utility>

template<typename Func>
struct foo {
    Func func;
};

template<typename Func>
foo<Func> make_foo(Func func)
{ return { std::move(func) }; }

int main()
{
    auto f = make_foo([] { return 42; });
    return f.func();
}
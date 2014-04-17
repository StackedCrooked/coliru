#include <type_traits>

template<class T>
struct split;
template<class Ret, class C>
struct split<Ret (C::*)()>
{
    using type = Ret;
};

struct foo
{
    int x;
    auto bar() -> decltype(foo::x);
    split<decltype(&foo::bar)>::type y;
};

int main()
{
    foo f; (void)f;
}
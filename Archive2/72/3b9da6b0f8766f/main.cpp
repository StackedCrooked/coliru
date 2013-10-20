#include <initializer_list>

struct foo
{
    foo(std::initializer_list<int>) {}
};

template<class T>
struct bar : T
{
    using T::T;
};

int main()
{
    bar<foo> b({1,2});
}

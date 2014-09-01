#include <iostream>
#include <array>
using namespace std;

struct Foo1
{
    struct init {};
};

struct Foo2 : public Foo1
{
    struct init{};
};

struct Foo3 : public Foo2
{
    struct init{};
};

template <typename... Args>
void Bar(typename Args::init... args)
{
    array<void*, sizeof...(Args) + 2> t = {nullptr, &args..., nullptr};
    for (size_t x = 1; x < sizeof...(Args) + 1; ++x)
        cout << t[x] << endl;
}

int main()
{
    Foo1::init a;
    Foo2::init b;
    Foo3::init c;
    Bar<Foo1, Foo2, Foo3>(a, b, c);
}

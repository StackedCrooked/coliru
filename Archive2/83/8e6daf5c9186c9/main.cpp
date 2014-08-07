#include <iostream>

constexpr int foo(const char* v)
{
    return v[0];
}

struct Bar
{
    static constexpr int foo(const char* v)
    {
        return v[0];
    }

    static constexpr const char* s = "abc";

    enum E : int;
};

enum Bar::E : int
{
    A = ::foo(s),
    B = Bar::foo(s)
};

int main()
{
    int a[Bar::A];
    a[0] = Bar::A;
}
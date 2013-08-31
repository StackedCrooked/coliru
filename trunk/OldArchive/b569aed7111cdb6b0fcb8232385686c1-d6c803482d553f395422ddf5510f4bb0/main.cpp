#include <iostream>

// culled by SFINAE if foo does not exist
template<typename T>
constexpr auto has_foo(int) -> decltype(std::declval<T>().foo, bool())
{
    return true;
}
// catch-all fallback for items with no foo
template<typename T> constexpr bool has_foo(...)
{
    return false;
}
//-----------------------------------------------------

template<typename T, bool>
struct GetFoo
{
    static int value(T& t)
    {
        return t.foo;
    }
};
template<typename T>
struct GetFoo<T, false>
{
    static int value(T&)
    {
        return 0;
    }
};
//-----------------------------------------------------

template<typename T>
int get_foo(T& t)
{
    return GetFoo<T, has_foo<T>(0)>::value(t);
}
//-----------------------------------------------------

struct Bar
{
    int val;
};

int main()
{
    Bar b { 5 };
    std::cout << get_foo(b) << std::endl;
    return 0;
}
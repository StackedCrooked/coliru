#include <type_traits>

struct foo
{
    int m;
    void bar()
    {
        static_assert(std::is_same<decltype(&foo::m), int (foo::*)>::value, "!");
        static_assert(std::is_same<decltype(&(foo::m)), int*>::value, "!");
    }
};

#include <iostream>

int main()
{
    foo f;
    f.bar();
}
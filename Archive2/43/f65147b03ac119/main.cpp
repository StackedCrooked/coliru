#include <unordered_map>
#include <utility>
#include <stdio.h>

struct FooBar
{
    FooBar(int* pFoo, int* pBar)
    {
        m_pFoo = pFoo;
        m_pBar = pBar;
        printf("Foobar default constructor called\n");
    };

    FooBar(FooBar const& rhs)
    {
        m_pBar = rhs.m_pBar;
        m_pFoo = rhs.m_pFoo;
        printf("Foobar copy constructor called\n");
    };

    FooBar(FooBar && rhs)
    {
        m_pBar = rhs.m_pBar;
        m_pFoo = rhs.m_pFoo;
        rhs.m_pBar = nullptr;
        rhs.m_pFoo = nullptr;
        printf("Foobar move constructor called\n");
    };

    int* m_pFoo;
    int* m_pBar;
};


int main()
{
    std::unordered_map<int, FooBar> map;
    map.emplace(std::piecewise_construct,
                std::forward_as_tuple(40),
                std::forward_as_tuple((int*)0xDEADBEEF, (int*)0x01010101));
}

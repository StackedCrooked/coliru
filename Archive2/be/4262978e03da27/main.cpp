#include <iostream>

struct s
{
    typedef void(*F)();
    operator F()       { std::cout<<"1"; return nullptr; } //#1
    operator F() const { std::cout<<"2"; return nullptr; } //#2
};

void foo(void(*)()) {}

void test(s& p)
{
    foo(p); //ambiguous function call with clang/EDG; gcc/VS call #1
}

int main()
{
    s x;
    test(x);
}
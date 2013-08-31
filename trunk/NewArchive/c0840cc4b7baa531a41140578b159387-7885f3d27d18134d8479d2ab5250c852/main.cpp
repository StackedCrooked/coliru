#include <cassert>
#include <iostream>

struct wup
{
    int i;
    void foo()
    {
        std::cout << (void*)this << std::endl;
    }
};

struct dup
{
    int j;
    void bar()
    {
        assert(this != nullptr);
        std::cout << (void*)this << std::endl;
    }
};

struct s : wup, dup
{
    void foobar()
    {
        foo();
        bar();
    }
};

int main()
{
    s* p = nullptr;
    p->foobar();
}

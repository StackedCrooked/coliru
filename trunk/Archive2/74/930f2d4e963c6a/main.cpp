#include <iostream>

template <typename F>
void run(F const &f)
{ f(42); }

struct foo
{
    foo()
    { run([&](auto){ work(); }); } /* change auto to int and it works */
    
    void work()
    { }
};

int main()
{
    foo{};
}

#include <initializer_list>

template<class... Args>
void foo(Args&&... args)
{
    auto x{ ([&]{ args = 42; }(), 0)... };
}

int main()
{
    volatile int i, j, k, l;
    foo(i, j, k, l);
    foo(i, j, k, l);
}
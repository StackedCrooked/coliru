#include <iostream>

template <typename T> class Foo;
template <typename T, typename... Args>
struct Foo<T(Args...)>
{
    // ...
    
    // ...
    
    template <typename... Uref>
    void operator() (Uref&&... args)
    {
        // Do work
    }
    template <typename Accumulator, typename... Uref>
    void operator() (Accumulator&& sink, Uref&&... args)
    {
        // Do more work
    }
};

int main()
{
    using namespace std;
    
    Foo<void(size_t)> foo;
    
    size_t a = __LINE__;
    
    foo(a);
    
    foo([&](size_t b)
    {
        // Do even more work
    },
    __LINE__);
}

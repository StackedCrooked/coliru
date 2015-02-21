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
        // ...
    }
    template <typename Accumulator, typename... Uref>
    void operator() (Accumulator&& sink, Uref&&... args)
    {
        sink(std::forward<Uref>(args)...);
    }
};

int main()
{
    using namespace std;

    Foo<void(size_t)> foo;

    // The following line matches the second operator() signature.
    // This is not desired.
    foo(__LINE__);

    auto c = [&](size_t b)
    {
        (void)b;
    };

    foo(c, __LINE__);
}

#include <utility>

template<typename Derived>
struct Base
{
    auto foo() -> decltype( std::declval<Derived&>().foo_impl() )
    {
        return static_cast<Derived*>(this)->foo_impl();
    }
};

struct Derived:
    public Base<Derived>
{
    auto foo_impl()
        -> int
    {
        return 0;
    }
};

int main()
{
    Derived b;
    int i = b.foo();
    (void)i;
}
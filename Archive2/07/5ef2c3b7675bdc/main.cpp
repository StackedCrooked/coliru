#include <iostream>

template<typename Derived>
struct B
{
    void doit(typename Derived::type x) { // <---- B needs Derived's type
        static_cast<Derived *>(this)->doit(x);
    }
};

struct D : B<D>
{
    using type = int;
};

int main(void) { }

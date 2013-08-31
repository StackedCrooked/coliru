#include <iostream>
#include <utility>

namespace A {
    struct B {};
    void swap(B&,B&)
    {
        std::cout << "A::swap";
    }
}

void swap(A::B&, A::B&)
{
    std::cout << "::swap";
}

template<class T>
using swap_func_type = void (*)(T &, T &);
template<class T>
swap_func_type<T> get_swap()
{
    //using std::swap;
    return static_cast<swap_func_type<T>>(swap);
}

int main()
{
    auto p = get_swap<A::B>();
    A::B b1, b2;
    p(b1, b2);
}

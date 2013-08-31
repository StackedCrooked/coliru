#include <iostream>

namespace detail
{
    template<int A, int B>
    struct helper
    {
        static void call() { std::cout << "f<A, B>()" << std::endl; }
    };

    template<int A>
    struct helper<A, A>
    {
        static void call() { std::cout << "f<A, A>()" << std::endl; }
    };
}

template<int a, int b>
void f()
{
    detail::helper<a, b>::call();
}

int main()
{
    f<1, 2>();
    f<1, 1>();
}

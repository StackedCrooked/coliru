template<class T>
struct B {};

#include <type_traits>

template<class T>
std::true_type foo(B<T>*);

std::false_type foo(void*);

struct D : B<int> {};
struct C {};

int main()
{
    using dptr = D*;
    static_assert( decltype(foo( dptr{} )){}, "!" );
}
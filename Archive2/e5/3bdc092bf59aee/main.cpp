#include <type_traits>

class X {};

template <typename T>
class Test
{
    static_assert( std::is_base_of<X,T>::value, "T doesn't derive from X!");
};

class A : public X {};

class B {};

Test<A> a; // OK
Test<B> b; // NOT OK
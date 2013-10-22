#include <type_traits>

struct Base
{
    class Foo {};
};

struct Derived : Base {};

static_assert( std::is_same< Base::Foo, Derived::Foo >::value, "Oops" );

int main()
{
    try {
        throw Derived::Foo();
    }
    catch( const Base::Foo& ) {}    
}

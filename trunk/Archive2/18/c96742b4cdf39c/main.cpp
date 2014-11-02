struct Foo
{
    Foo* test = this;
    using self = decltype(test);
    
    static void smf()
    {
        self foo;
    }
};

#include <iostream>
#include <type_traits>

int main()
{
    static_assert( std::is_same< Foo::self, Foo* >::value, "" );
}

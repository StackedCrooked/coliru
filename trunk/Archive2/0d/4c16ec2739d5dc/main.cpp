#include <type_traits>

class A { ~A(); };

int main()
{
    static_assert( !std::is_constructible<A>{}, "" );   
}



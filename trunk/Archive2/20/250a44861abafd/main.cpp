#include <type_traits>

namespace detail
{
    template<typename F>
    F multiplier = F(101.0);
}

template <typename T> T foo( T x )
{
    static_assert( std::is_floating_point<T>::value, "" );
    
    T y = x * detail::multiplier<T>;
    
    static_assert(std::is_same<decltype(detail::multiplier<T>), T>{}, "");

    return( y );
}

#include <iostream>

int main()
{
    std::cout << foo(1.0) << std::endl;
    std::cout << foo(1.0f) << std::endl;
}

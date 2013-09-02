#include <type_traits>

template<typename T>
auto one(T t) -> decltype(t);

template<typename T>
auto two(T t) -> decltype( t < t, t );

int main()
{
    static_assert( std::is_same<decltype( one(0) ), decltype( two(0) )>(), "" );
}
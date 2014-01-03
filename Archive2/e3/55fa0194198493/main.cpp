#include <string>
#include <type_traits>

template< typename T >
void verify_pod()
{
    static_assert( std::is_pod<T>::value, "T is not a POD" );
}

int main()
{
    verify_pod< std::string >();
}

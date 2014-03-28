#include <type_traits>
#include <array>

using namespace std;


template<typename T>
struct array_size : std::extent<T> { };

template<typename T, size_t N>
struct array_size<std::array<T,N> > : std::tuple_size<array<T,N> > { };

template < typename T >
void foo( T& param )
{
    using U = typename std::remove_cv<typename std::remove_reference<T>::type>::type;
	static_assert( 3 == array_size<U>::value, "param must have a size of 3" );
}

int main( void )
{
    int cArray[3];
    std::array< int, 3 > stdArray;

    foo( cArray );
    foo( stdArray );
}


#include <type_traits>

template< typename T >
using bare = std::remove_cv_t< std::remove_reference_t< T > >;

template< typename T >
using param = std::conditional_t< sizeof( T ) <= sizeof( void* ) , bare< T > , std::add_const_t< std::add_lvalue_reference_t< bare< T > > > >;
    
template< typename T , typename TNum >
T operator * ( const T& t , param< TNum > num ) {
    return T();
}

struct A {};
struct BigInt {};

int main() {
    A a;
    BigInt i;

	A result = a * i;
	result = a * 1.0f;
}

#include <iostream>
#include <string>
#include <vector>

struct HasStuff { static void stuff( int, char ); };
struct HasNoStuff { };

void stuff( int, char ) {}

template < typename T >
struct stuff_exists
{
    struct __Fallback { static void stuff( int, char ); };
	struct __Derived : T, __Fallback { };

	template< typename U, U >
	struct __Ambiguous;

	template < typename U >
	static char ( &__check( __Ambiguous<void (*)(int, char), &U::stuff> * ) ) [1];

	template < typename U >
	static char ( &__check( ... ) )[2];

	static bool const value = sizeof( __check<__Derived>( 0 ) ) == 2;
};

int main()
{
	std::cout << std::boolalpha;

	std::cout << stuff_exists<HasStuff>::value << std::endl;
	std::cout << stuff_exists<HasNoStuff>::value << std::endl;

	return 0;
}
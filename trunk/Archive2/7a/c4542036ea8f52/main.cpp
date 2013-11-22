#include <iostream>
#include <string>
#include <vector>

void stuff( int, char );

struct HasStaticStuff { static void stuff( int, char ); };
struct HasMemberStuff { void stuff( int, char ); };
struct HasStaticWrongSig { static void stuff( float, char ); };
struct HasMemberWrongSig { void stuff( int, float ); };
struct HasMemberNotFunction { int stuff; };
struct HasNoStuff { };

void stuff( int, char ) {}

template < typename T >
struct stuff_exists
{
    static const int _True = 1;
	static const int _False = 2;

	struct __dummy;
	struct __Fallback { __dummy* stuff; };
	struct __Derived : T, __Fallback { };

	template< typename U, U >
	struct __Ambiguous;

	template < typename U >
	static char ( &__check_nameExists( __Ambiguous<__dummy* __Fallback::*, &U::stuff> * ) ) [_False];

	template < typename U >
	static char ( &__check_nameExists( ... ) )[_True];

	template < typename V >
	static char ( &__check_functionSignature( void ( T::* )( int t, char b ) ) ) [_True];

	template < typename V >
	static char ( &__check_functionSignature( void ( * )( int t, char b ) ) ) [_True];

	template < typename V >
	static char ( &__check_functionSignature( ... ) ) [_False];

	static bool const _nameExists = sizeof( __check_nameExists<__Derived>( 0 ) ) == _True;
	static bool const _signatureMatch = sizeof( __check_functionSignature<T>( &T::stuff ) ) == _True;
	static bool const value =  _nameExists && _signatureMatch;
};

int main()
{
	std::cout << std::boolalpha;

	std::cout << stuff_exists<HasStaticStuff>::value << std::endl;
	std::cout << stuff_exists<HasMemberStuff>::value << std::endl;
	std::cout << stuff_exists<HasStaticWrongSig>::value << std::endl;
	std::cout << stuff_exists<HasMemberWrongSig>::value << std::endl;
	std::cout << stuff_exists<HasMemberNotFunction>::value << std::endl;
	//std::cout << stuff_exists<HasNoStuff>::value << std::endl; // last bug

	//system("pause");
	return 0;
}
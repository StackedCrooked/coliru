#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <type_traits>

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

	struct __Fallback { struct __dummy* stuff; };
	struct __Derived : T, __Fallback { };

	template< typename U, U >
	struct __Ambiguous;

	template < typename V >
	static char ( &__check_nameExists( __Ambiguous<__dummy* __Fallback::*, &V::stuff> * ) ) [_False];

	template < typename V >
	static char ( &__check_nameExists( ... ) ) [_True];

	template < bool Enabled, typename EnabledType = void >
	struct __check_functionSignature { static bool const value = false; };

	template < bool Enabled >
	struct __check_functionSignature< Enabled, typename std::enable_if< Enabled >::type >
	{ 
		template < typename W >
		static char ( &__check( void ( W::* )( int t, char b ) ) ) [_True];

		template < typename W >
		static char ( &__check( void ( * )( int t, char b ) ) ) [_True];

		template < typename W >
		static char ( &__check( ... ) ) [_False];

		static bool const value = sizeof( __check< T >( &T::stuff ) ) == _True;
	};

	static bool const _nameExists = sizeof( __check_nameExists<__Derived>( 0 ) ) == _True;
	static bool const value =  _nameExists && __check_functionSignature<_nameExists>::value;
};

template< typename T >
void PrintTest()
{
	std::cout << typeid(T).name() << "\t\t" << stuff_exists<T>::value << std::endl;
}

int main()
{
	std::cout << std::boolalpha;

	PrintTest<HasStaticStuff>();
	PrintTest<HasMemberStuff>();
	PrintTest<HasStaticWrongSig>();
	PrintTest<HasMemberWrongSig>();
	PrintTest<HasMemberNotFunction>();
	PrintTest<HasNoStuff>();

	//system("pause");
	return 0;
}
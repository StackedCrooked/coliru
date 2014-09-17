#include <type_traits> // To use 'std::integral_constant'.
#include <iostream>    // To use 'std::cout'.
#include <iomanip>     // To use 'std::boolalpha'.

// The old style how we detect existence of a member type
// http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Member_Detector
template<typename T>
class has_member_type_type
{
    using Yes = char[2];
	using  No = char[1];

	struct Fallback { struct type; };
	struct Derived : T, Fallback { };

	template < typename U >
	static No& test( typename U::type* );
	template < typename U >
	static Yes& test(...);

public:
	static const bool value = sizeof( test<Derived>( nullptr ) ) == sizeof( Yes );
};


//template< class... > using void_t = void;
// The following two uncommented lines for substitute the above one line because of a gcc problem
// (the standard does not specify what to do with unused template params)
template< class... > struct voider { using type = void; };
template< class... T0toN > using void_t = typename voider<T0toN...>::type;

// The new way to detect the member type, if it is valid!
template< class, class = void >
struct has_type_member : std::false_type { };
template< class T >
struct has_type_member<T, void_t<typename T::type>> : std::true_type { };

struct A { struct type; };
struct B { using type = int; };
// has_member_type_type also works on ambiguous types like C::type.
struct C : A, B {};

int main ( )
{
	std::cout << std::boolalpha
			  << "'type' in 'A' : " << has_member_type_type<A>::value << "\n";
	std::cout << std::boolalpha
			  << "'type' in 'A' : " << has_type_member<A>::value << "\n";

	std::cout << std::boolalpha
			  << "'type' in 'B' : " << has_member_type_type<B>::value << "\n";
	std::cout << std::boolalpha
			  << "'type' in 'B' : " << has_type_member<B>::value << "\n";

	std::cout << std::boolalpha
			  << "'type' in 'C' : " << has_member_type_type<C>::value << "\n";
	std::cout << std::boolalpha
			  << "'type' in 'C' : " << has_type_member<C>::value << "\n";
}


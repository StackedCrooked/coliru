#include <type_traits>
#include <tuple>

// find the index of a type in a list of types,
// return sizeof...(Ts) if T is not found
template< typename T, typename... Ts >
struct index_by_type : std::integral_constant< std::size_t, 0 > {};

template< typename T, typename... Ts >
struct index_by_type< T, T, Ts... > : std::integral_constant< std::size_t, 0 >
{
   static_assert( index_by_type< T, Ts... >::value == sizeof...( Ts ), "duplicate type detected" );
};

template< typename T, typename U, typename... Ts >
struct index_by_type< T, U, Ts... > : std::integral_constant< std::size_t, index_by_type< T, Ts... >::value + 1 > {};

// get the element from either "us" if possible...
template< std::size_t I, std::size_t J, typename T, typename... Us, typename... Ts >
auto get_by_index( const std::tuple< Us... >&, const std::tuple< Ts... >& ts )
   -> typename std::enable_if< I == sizeof...( Us ), const T& >::type
{
   return std::get< J >( ts );
}

// ...get the element from "ts" otherwise
template< std::size_t I, std::size_t J, typename T, typename... Us, typename... Ts >
auto get_by_index( const std::tuple< Us... >& us, const std::tuple< Ts... >& )
   -> typename std::enable_if< I != sizeof...( Us ), const T& >::type
{
   return std::get< I >( us );
}

// helper to validate that all Us are in Ts...
template< bool > struct invalide_type;
template<> struct invalide_type< true > : std::true_type {};
template< std::size_t... > void validate_types() {}

template< typename... Ts >
struct dflt
{
   static const std::tuple< Ts... > value;
};

template< typename... Ts >
const std::tuple< Ts... > dflt< Ts... >::value;

// reorder parameters
template< typename... Ts, typename... Us >
std::tuple< const Ts&... > ordered_tie( const Us&... us )
{
   auto tmp = std::tie( us... );
   validate_types< invalide_type< index_by_type< const Us&, const Ts&... >::value != sizeof...( Ts ) >::value... >();
   return std::tie( get_by_index< index_by_type< const Ts&, const Us&... >::value,
                              index_by_type< const Ts&, const Ts&... >::value, Ts >( tmp, dflt< Ts... >::value )... );
}

struct A {};
struct B {};
struct C {};

struct Gadget
{
   A a;
   B b;
   C c;

   explicit Gadget( const std::tuple< const A&, const B&, const C& >& t )
      : a( std::get<0>(t) ),
        b( std::get<1>(t) ),
        c( std::get<2>(t) )
   {}

   template< typename... Ts >
   Gadget( const Ts&... ts ) : Gadget( ordered_tie< A, B, C >( ts... ) ) {}
};

int main()
{
   A a;
   B b;
   C c;

   Gadget g1( a, b, c );
   Gadget g2( b, c, a );
   Gadget g3( a, b ); // uses a default-constructed C
   Gadget g4( a, c ); // uses a default-constructed B
   Gadget g5( c ); // uses a default-constructed A and B
   Gadget g6; // uses a default-constructed A, B and C

   // fails to compile:
   // Gadget gf1( a, a ); // duplicate type
   // Gadget gf2( a, b, 42 ); // invalid type
}

#include <tuple>

template< typename... TYPES > struct type_seq {};

template< typename... TYPES > struct size {} ;
template< typename... TYPES > struct size< type_seq<TYPES...> >
{ enum { value = sizeof...(TYPES) } ; } ;

template< typename... TYPES > struct front {} ;
template< typename T, typename... TYPES > struct front< type_seq< T, TYPES... > >
{ using type = T ; };

template< typename T, typename... TYPES > struct push_front {} ;
template< typename T, typename... TYPES > struct push_front< T, type_seq<TYPES...> >
{ using type = type_seq< T, TYPES... >; } ;

template< typename... TYPES > struct pop_front {} ;
template< typename T, typename... TYPES > struct pop_front< type_seq< T, TYPES... > >
{ using type = type_seq<TYPES...> ; } ;

template< unsigned int N, typename... TYPES > struct at {} ;
template< unsigned int N, typename... TYPES > struct at< N, type_seq<TYPES...> >
{ using type = typename std::tuple_element< N, std::tuple<TYPES...> >::type ; };

template< typename T, typename U, int N = 0 > struct index_of ;
template< typename T, int N > struct index_of< T, type_seq<>, N > { enum { value = -1 } ; };
template< typename T, typename FIRST, typename ...REST, int N >
struct index_of< T, type_seq<FIRST,REST...>, N >
          : std::conditional< std::is_same<T,FIRST>::value,
                                std::integral_constant<std::size_t,N>,
                                index_of< T, type_seq<REST...>, N+1 > >::type {} ;
// etc.

struct UndeadMonster { virtual ~UndeadMonster() = default ; /* ... */ };
struct Skeleton : UndeadMonster { /* ... */ } ;
struct Zombie : UndeadMonster { /* ... */ } ;
struct Ghoul : UndeadMonster { /* ... */ } ;

using undead_types = type_seq< Skeleton, Zombie, Ghoul > ;

int main()
{
    static_assert( std::is_same< at<1,undead_types>::type, Zombie >::value, "not ok" ) ;
    
    static_assert( index_of< Ghoul, undead_types >::value == 2, "not ok" ) ;

    using T = push_front< double, push_front< int, undead_types >::type >::type ;
    static_assert( index_of< Ghoul, T >::value == 4, "not ok" ) ;
}

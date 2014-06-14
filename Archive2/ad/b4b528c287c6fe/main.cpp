#include <iostream>
#include <tuple>
#include <type_traits>

template < typename... > struct pop_front ;

template < typename FIRST, typename... REST >
struct pop_front< std::tuple< FIRST, REST... > > { using type = std::tuple<REST...> ; };
// ----------------------------------------------------------------

template < typename... > struct push_front ;

template < typename T, typename... U >
struct push_front< T, std::tuple< U... > > { using type = std::tuple< T, U... > ; };
// ----------------------------------------------------------------

template < std::size_t SKIP, typename... T > struct tail ;

template < std::size_t SKIP, typename...T >
struct tail< SKIP, std::tuple<T...> >
{
    static_assert( std::tuple_size< std::tuple<T...> >::value > SKIP, "tuple is too small" ) ;
    using type = typename tail< SKIP-1, typename pop_front< std::tuple<T...> >::type >::type ;
};

template < typename...T > struct tail< 0, std::tuple<T...> > { using type = std::tuple<T...>; };
// ----------------------------------------------------------------

template < std::size_t TAKE, typename... T > struct head ;

template < std::size_t TAKE, typename FIRST, typename... REST >
struct head< TAKE, std::tuple< FIRST, REST... > >
{
    static_assert( std::tuple_size< std::tuple<FIRST,REST...> >::value >= TAKE, "tuple is too small" ) ;
    using type = typename push_front< FIRST, typename head< TAKE-1, std::tuple<REST...> >::type >::type ;
};

template < typename FIRST, typename... REST >
struct head< 1, std::tuple< FIRST, REST... > > { using type = std::tuple<FIRST> ; };
// ----------------------------------------------------------------

template < std::size_t SKIP, std::size_t TAKE, typename... > struct sub_tuple ;

template < std::size_t SKIP, std::size_t TAKE, typename... T > struct sub_tuple< SKIP, TAKE, std::tuple<T...> >
{
    using type = typename head< TAKE, typename tail< SKIP, std::tuple<T...> >::type >::type ;
};
// ----------------------------------------------------------------

template < std::size_t SKIP, std::size_t TAKE > struct extract_sub_tuple
{
    template< typename... T >
    typename sub_tuple< SKIP, TAKE, std::tuple<T...> >::type operator() ( const std::tuple<T...>& tuple ) const
    { return std::tuple_cat( std::make_tuple( std::get<SKIP>(tuple) ), extract_sub_tuple< SKIP+1, TAKE-1 >()(tuple) ) ; }
};

template < std::size_t SKIP > struct extract_sub_tuple< SKIP, 0 >
{
    template< typename... T >
    std::tuple<> operator() ( const std::tuple<T...>& ) const { return std::tuple<>() ; }
};
// ----------------------------------------------------------------

int main()
{
    using type = sub_tuple< 2, 4, std::tuple< char, char16_t, char32_t, wchar_t, short, int, long, long long > >::type ;
    static_assert( std::is_same< type, std::tuple< char32_t, wchar_t, short, int > >::value, "not ok" ) ;

    std::tuple< char, char16_t, char32_t, wchar_t, short, long, long long > tup( 0, 1, 2, 3, 4, 5, 6 ) ;
    type sub_tuple = extract_sub_tuple<2,4>()(tup) ;
    std::cout << std::boolalpha << ( sub_tuple == std::make_tuple(2,3,4,5) ) <<  '\n' ;
}

#include <type_traits>
#include <utility>

namespace detail
{
    using two_chars = char(&)[2] ;

    template < typename T > struct has_iterator
    {
        template < typename U > static char test( const typename U::iterator* ) ;
        template < typename U > static two_chars test( ... ) ;
        static constexpr bool value = sizeof( test<T>(nullptr) ) == sizeof(char) ;
    };

    template < typename T > struct has_key_type
    {
        template < typename U > static char test( const typename U::key_type* ) ;
        template < typename U > static two_chars test( ... ) ;
        static constexpr bool value = sizeof( test<T>(nullptr) ) == sizeof(char) ;
    };

    template < typename T, typename = void > struct has_insert : std::false_type {};
    template < typename T > struct has_insert< T, typename std::enable_if< has_key_type<T>::value >::type >
    {
        using insert_t = std::pair< typename T::iterator, bool > (T::*)( const typename T::key_type& ) ;
        template < typename U > static char test( const insert_t* ) ;
        template < typename U > static two_chars test( ... ) ;
        static constexpr bool value = sizeof( test<T>(nullptr) ) == sizeof(char) ;
    };

    template < typename T, typename = void > struct has_find : std::false_type {};
    template < typename T >
    struct has_find< T, typename std::enable_if< has_iterator<T>::value && has_key_type<T>::value >::type >
    {
        using find_t = typename T::iterator (T::*)( const typename T::key_type& ) ;
        template < typename U > static char test( const find_t* ) ;
        template < typename U > static two_chars test( ... ) ;
        static constexpr bool value = sizeof( test<T>(nullptr) ) == sizeof(char) ;
    };
}

template < typename T >
struct is_associative_container : std::conditional< detail::has_iterator<T>::value &&
                                                    detail::has_key_type<T>::value &&
                                                    detail::has_insert<T>::value &&
                                                    detail::has_find<T>::value,

                                                    std::true_type,
                                                    std::false_type >::type {};

#include <set>
#include <unordered_map>
#include <iostream>

int main()
{
    using T = const std::set<int> ;
    using U = volatile std::unordered_multimap<int,int> ;
    std::cout << std::boolalpha << is_associative_container<T>::value << '\n'
                                << is_associative_container<U>::value << '\n' ;
}

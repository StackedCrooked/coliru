#include <iostream>
#include <type_traits>
#include <memory>

namespace utility
{
    template < typename, typename... > struct cnt_convertible ;
    template < typename A, typename B > struct cnt_convertible<A,B>
    { static constexpr std::size_t value = std::is_convertible<A,B>::value ; };
    template < typename A, typename FIRST, typename... REST > struct cnt_convertible<A,FIRST,REST...>
    { static constexpr std::size_t value = cnt_convertible<A,FIRST>::value + cnt_convertible<A,REST...>::value ; };

    template < bool CONDITION > struct true_if : std::conditional< CONDITION, std::true_type, std::false_type >::type {} ;

    template < typename... T > struct all_are_convertible : true_if< cnt_convertible<T...>::value == ( sizeof...(T) - 1 ) > {} ;
    template < typename... T > struct none_are_convertible : true_if< cnt_convertible<T...>::value == 0 > {} ;
    template < typename... T > struct few_are_convertible : true_if< !all_are_convertible<T...>::value &&
                                                                     !none_are_convertible<T...>::value > {};
    // etc.
}

template < typename... TYPES >
typename std::enable_if< utility::all_are_convertible<int,TYPES...>::value >::type foo( TYPES&&...)
{ std::cout << "all are implicitly convertible to int\n" ; }

template < typename... TYPES >
typename std::enable_if< utility::few_are_convertible<int,TYPES...>::value >::type foo( TYPES&&...)
{ std::cout << "some, but not all, are implicitly convertible to int\n" ; }

template < typename... TYPES >
typename std::enable_if< utility::none_are_convertible<int,TYPES...>::value >::type foo( TYPES&&...)
{ std::cout << "none are implicitly convertible to int\n" ; }

int main()
{
    foo( 'a', 56L, 75ULL, !std::addressof(std::cout), 0 ) ; // all are implicitly convertible to int
    foo( 'a', 56L, 75ULL, std::allocator_arg, 0, std::cout, 0 ) ; // some, but not all, are implicitly convertible to int
    foo( std::addressof(std::cout), std::allocator_arg, std::cout ) ; // none are implicitly convertible to int
}

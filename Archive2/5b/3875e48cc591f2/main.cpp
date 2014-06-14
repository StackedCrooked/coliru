#include <iostream>
#include <tuple>

template < std::size_t SKIP, std::size_t TAKE > struct extract_sub_tuple
{
    template< typename... T >
    auto operator() ( const std::tuple<T...>& tuple ) const 
        -> decltype( std::tuple_cat( std::make_tuple( std::get<SKIP>(tuple) ), extract_sub_tuple< SKIP+1, TAKE-1 >()(tuple) ) ) 
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

    std::tuple< char, char16_t, char32_t, wchar_t, short, long, long long > tup( 0, 1, 2, 3, 4, 5, 6 ) ;
    auto sub_tuple = extract_sub_tuple<2,4>()(tup) ;
    std::cout << std::boolalpha << ( sub_tuple == std::make_tuple(2,3,4,5) ) <<  '\n' ;
}

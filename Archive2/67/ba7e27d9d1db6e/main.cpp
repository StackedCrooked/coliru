#include <iostream>
#include <type_traits>
#include <vector>

template < typename T > struct is_vector : std::false_type {} ;
template < typename T > struct is_vector< std::vector<T> > : std::true_type {} ;

template < typename T > typename std::enable_if< is_vector<T>::value, T >::type
get_param( std::string path )
{
    std::cout << "get_param( " << path << " ) : overload for vector\n" ;
    // ...
    return T{} ;
}

template < typename T > typename std::enable_if< !is_vector<T>::value, T >::type
get_param( std::string path )
{
    std::cout << "get_param( " << path << " ) : overload for non-vector\n" ;
    // ...
    return T{} ;
}

int main()
{
    auto v = get_param< std::vector<int> >( "hello vector " ) ;
    auto i = get_param<int>( "hello non-vector" ) ;
    v.push_back(i) ;
}

#include <iostream>
#include <iomanip>

#include <cstdlib>

template< typename ...types >
struct B
{
    
};

template< typename ...types >
struct D : B< types... > 
{

    using B< types... >::B;

};

template< typename ...types > 
constexpr 
std::true_type 
helper(B< types... > const &)
{
    return {};
}

template< typename T > 
constexpr 
std::false_type 
helper(T &&)
{
    return {};
}

int 
main()
{
    std::cout << std::boolalpha << std::is_same< std::true_type, decltype(helper(std::declval< D< int > const & >())) >::value << std::endl;
    return EXIT_SUCCESS;
}

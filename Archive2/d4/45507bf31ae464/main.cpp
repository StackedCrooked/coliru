#include <utility>
#include <tuple>
#include <iostream>

template < size_t I = 0, typename... Args >
auto recursive_function( std::tuple< Args... > const& t )
    -> typename std::enable_if< I == sizeof...(Args), void >::type
{

}


template < size_t I = 0, typename... Args >
auto recursive_function( std::tuple< Args...>const & t )
    -> typename std::enable_if< I < sizeof...(Args), void >::type
{
    std::cout << std::get<I>(t) << '\n';
    int i = 0;
    recursive_function< I + 1, Args... >( t );
}


int main() {
    std::tuple<int, char, double> x {1, 'a', 3.14};
    recursive_function(x);
}
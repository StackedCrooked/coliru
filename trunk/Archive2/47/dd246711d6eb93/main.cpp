#include <iostream>
#include <type_traits>

#include <boost/mpl/or.hpp>

template<typename T>
using type = boost::mpl::or_<
                std::is_same<T, char>,
                std::is_same<T, int>
             >;
int main() 
{
    std::cout << type<int>::value << std::endl;
    std::cout << type<long>::value << std::endl;
}

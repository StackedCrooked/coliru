/////////////// SCARY iterators check /////////////////////////

#include <iostream>
#include <iterator>
#include <set>
#include <functional>
#include <type_traits>
//#include <boost/pool/pool_alloc.hpp>

int main()
{
    using set_one = std::set<int> ;

    // container with different comparator /*, different allocator */
    using set_two = std::set< int, std::greater<int> /*, boost::pool_allocator<int> */ > ;

    constexpr bool cntrs_of_same_type = std::is_same< set_one, set_two >::value ;
    std::cout << "containers are of same type? " << std::boolalpha
               << cntrs_of_same_type << '\n' ; // false

    using iter_one = set_one::iterator ;
    using iter_two = set_two::iterator ;

    // is iter_type_one the same as iter_type_two?
    constexpr bool iters_of_same_type = std::is_same< iter_one, iter_two >::value ;
    std::cout << "SCARY iterators? " << iters_of_same_type << '\n' ; // true
}

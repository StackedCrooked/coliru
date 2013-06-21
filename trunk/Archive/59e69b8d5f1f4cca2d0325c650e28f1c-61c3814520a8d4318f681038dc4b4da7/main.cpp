#include <iostream>
#include <ios>
#include <string>
#include <boost/algorithm/string/predicate.hpp>

int main()
{
    std::string str("Hello world!");
    std::cout << "str = " << str << '\n';
    
    using boost::algorithm::contains;  // case sensitive 
    using boost::algorithm::icontains; // case insensitive

    std::cout << std::boolalpha;
    
    // case sensitive 
    bool contains_hello = contains(str, "hello");
    std::cout << "contains_hello = " << contains_hello << '\n';

    // case insensitive 
    bool icontains_hello = icontains(str, "hello");
    std::cout << "icontains_hello = " << icontains_hello << '\n';

    std::cout << std::noboolalpha;

    return 0;
}


#include <iostream>
#include <set>
#include <string>
#include <iterator>

int main()
{
    std::set<std::string> set { "int", "main()", "#include", "<iterator>", "#include", "<string>", "<set>", "<iostream>" };

    {
        // range-based loop 
        for( const auto& str : set ) std::cout << str << ' ' ;
        std::cout << '\n' ;
    }

    {
        // iterators
        for( auto iter = std::begin(set) ; iter != std::end(set) ; ++iter ) std::cout << *iter << ' ' ;
        std::cout << '\n' ;

        // iterators, in reverse
        for( auto iter = set.rbegin() ; iter != set.rend() ; ++iter ) std::cout << *iter << ' ' ;
        std::cout << '\n' ;
    }

    {
        // iterators (legacy)
        for( std::set<std::string>::iterator iter = set.begin() ; iter != set.end() ; ++iter ) std::cout << *iter << ' ' ;
        std::cout << '\n' ;

        // iterators, in reverse (legacy)
        for( std::set<std::string>::reverse_iterator iter = set.rbegin() ; iter != set.rend() ; ++iter ) std::cout << *iter << ' ' ;
        std::cout << '\n' ;
    }
}

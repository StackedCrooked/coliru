#include <iostream>
#include <iterator>
#include <vector>
#include <string>

template < typename ITERATOR >
void perms( std::string str, ITERATOR begin, ITERATOR end )
{
    if( begin != end )
        for( char c : *begin ) perms( str+c, std::next(begin), end ) ;
    else
    {
        static constexpr int WIDTH = 120 ;
        static int w = 0 ;

        w += str.size() + 3 ;
        if( w > WIDTH ) { std::cout << '\n' ; w = str.size() + 3  ; }
        std::cout << '"' << str << "\" " ;
    }
}

template < typename PERM_LIST > void perms( const PERM_LIST& list )
{ perms( "", list.begin(), list.end() ) ; }

int main()
{
    std::vector<std::string> perm_list = { "ab", "cdefg", "hij", "klmn", "opq", "rstuvw", "xyz" } ;
    perms( perm_list ) ;
}

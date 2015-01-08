#include <iostream>
#include <cctype>
#include <map>

void freq( const char* cstr ) // *** const
{
    if(cstr)
    {
        std::map<char,int> freq ;
        for( ; *cstr ; ++cstr ) if( std::isalpha(*cstr) ) ++freq[ std::tolower(*cstr) ] ;
        for( auto pair : freq ) std::cout << pair.first << ' ' << pair.second << '\n' ;
    }
}

int main()
{
    freq( "We accept reality so readily, perhaps because we sense that nothing is real." ) ;
}

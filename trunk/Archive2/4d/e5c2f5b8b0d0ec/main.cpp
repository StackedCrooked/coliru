#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

int main()
{
    const std::string str = "it. is? awesome!" ;

    {
        // simple
        std::string a ;
        for( char c : str ) if( std::isalnum(c) ) a += c ;
        std::cout << a << '\n' ;
    }

    {
        // complicated: after erasing, stay at the same position for the next char
        // but cater to the erase having reduced the size of the string
        std::string b = str ;
        for( std::size_t i = 0 ; i < b.size() ; ++i )
            while( !std::isalnum( b[i] ) && i < b.size() ) b.erase(i,1) ;
        std::cout << b << '\n' ;
    }

    {
        // erase(iterator) returns the iterator following the erased character.
        // http://en.cppreference.com/w/cpp/string/basic_string/erase
        std::string c = str ;
        for( std::string::iterator iter = c.begin() ; iter != c.end() ; )
            if( !std::isalnum(*iter) ) iter = c.erase(iter) ;
            else ++iter ; // not erased, increment iterator
        std::cout << c << '\n' ;
    }

    {
        // erase-remove idiom https://en.wikipedia.org/wiki/Erase-remove_idiom
        std::string d = str ;
        d.erase( std::remove_if( d.begin(), d.end(), []( char c ) { return !std::isalnum(c) ; } ), d.end() ) ;
        std::cout << d << '\n' ;
    }
}

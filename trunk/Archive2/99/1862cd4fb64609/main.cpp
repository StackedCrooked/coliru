#include <iostream>
#include <sstream>
#include <string>

struct my_stream : std::istream
{
    my_stream() : std::istream( std::cin.rdbuf() ) {}

    template < typename T > my_stream& operator>> ( T& v )
    {
        if( static_cast<std::istream&>(*this) >> v ) strstm << v << '\n' ;
        return *this ;
    }

    // likeweise for get(), unget(), getline() etc

    void rewind()
    {
        clear() ; // just to be safe
        rdbuf( strstm.rdbuf() ) ;
        strstm.clear(std::ios::failbit) ; // supress further output to strstm
    }

    std::stringstream strstm ;
};

// overload non-member getline() (if required)

int main()
{
    my_stream stm ;

    std::string str ;
    for( int i = 0 ; i < 5 ; ++i )
    {
        stm >> str ;
        std::cout << "read from stdin: " << str << '\n' ;
    }

    stm.rewind() ;
    while( stm >> str ) std::cout << "reread from stream: " << str << '\n' ;
}

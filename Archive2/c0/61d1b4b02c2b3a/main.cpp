#include <iostream>
#include <sstream>
#include <string>

struct my_stream : std::istream
{
    // initially read from the stream buffer of std::cin
    my_stream() : std::istream( std::cin.rdbuf() ) {} 

    template < typename T > my_stream& operator>> ( T& v )
    {
        // dor formatted input, begabe exactly as a std::istream would
        if( static_cast<std::istream&>(*this) >> v ) 
               strstm << v << '\n' ; // but save what has been read into the auxiliary stream
        return *this ;
    }

    // likeweise for get(), unget(), getline() etc

    void rewind() // switch the stream buffer to read from the stream buffer to which input was saved
    {
        clear() ; // just to be safe
        rdbuf( strstm.rdbuf() ) ; // switch streambuf
        strstm.clear(std::ios::failbit) ; // supress further output to strstm
    }

    std::stringstream strstm ; // contains a copy of the input
};

// overload non-member getline() (if required)

int main()
{
    my_stream stm ;
    
    int n ;
    std::string str ;
    for( int i = 0 ; i < 5 ; ++i ) // read from stdin
    {
        stm >> n >> str ;
        std::cout << "read from stdin: " << n << ' ' << str << '\n' ;
    }
    
    std::cout << "--------------------------\n" ;
    
    stm.rewind() ; // re-read what was read earlier
    while( stm >> n >> str ) std::cout << "re-read from stream: " << n << ' ' << str << '\n' ;
}

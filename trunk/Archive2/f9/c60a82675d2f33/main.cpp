#include <iostream>
#include <sstream>

static int n = 0 ;

template < typename T >
std::ostream& print( std::ostream& stm, const T& t ) ; // **** declare #2

template < typename T, typename... ARGS >
std::ostream& print( std::ostream& stm, const T& t, const ARGS&... args ) // #1
{ 
    std::clog << "  " << ++n << ". variadic: std::ostream& print( std::ostream& stm, const T& t, const ARGS&... args ) // #1\n" ; 
    return print( stm << t, args... ) ; 
}

template < typename T >
std::ostream& print( std::ostream& stm, const T& t ) // #2
{ 
    std::clog << "  " << ++n << ". non-variadic: std::ostream& print( std::ostream& stm, const T& t ) // #2\n" ; 
    return stm << t  ; 
}

int main()
{
    std::stringbuf strbuf ;
    const auto oldbuf = std::clog.rdbuf( std::addressof(strbuf) ) ;
    print( std::cout, 1, 2 ) << '\n' << std::flush ;
    std::cout << "sequence of calls were:\n" << strbuf.str() ;
    std::clog.rdbuf(oldbuf) ;
}

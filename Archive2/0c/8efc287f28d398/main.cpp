#include <iostream>

struct endl_n_ { explicit constexpr endl_n_( int n = 2 ) noexcept : cnt(n) {} ; const int cnt ; };

template < typename C, typename T >
std::basic_ostream<C,T>& operator<< ( std::basic_ostream<C,T>& stm, endl_n_ en )
{
    for( int i = 0 ; i < en.cnt ; ++i ) stm.put( stm.widen('\n') ) ;
    return stm.flush() ;
}

constexpr endl_n_ endln( int c ) noexcept { return endl_n_(c) ; }

template < typename C, typename T >
std::basic_ostream<C,T>& endl2( std::basic_ostream<C,T>& stm ) { return stm << endln(2) ; }

int main()
{
    std::cout << 'a' << endl2 << 'b' << endln(3) << 'c' << '\n' ;
    std::wcout << L'd' << endl2 << L'e' << endln(3) << L'f' << L'\n' ;
}

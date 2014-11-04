#include <iostream>

struct eat_char
{
    eat_char( char c ) : ch(c) {}
    const char ch ;
};

std::istream& operator>> ( std::istream& stm, eat_char ec )
{
    char c ;

    if( stm >> c )
    {
        if( c == ec.ch ) return stm ;
        else stm.putback(c) ;
    }

    stm.clear(std::ios::failbit) ;
    return stm ;
}

int main()
{
    int a, b, c ;
    while( std::cin >> a >> '/' >> b >> ':' >> c )
        std::cout << a << ' ' << b << ' ' << c << '\n' ;
}

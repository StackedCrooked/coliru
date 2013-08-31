#include <list>
#include <iostream>

typedef std::list< int > lst;

void doPrint( const lst & l )
{
    lst::const_iterator i = l.begin();
    while ( i != l.end() ) {
        std::cout << " " << *i++;
    }
    std::cout << "\n";
}


int main(int argc, char* argv[])
{
    lst l;
    for( int i = 0; i < 10; ++i )
        l.push_back( i );

    doPrint( l );
    lst::iterator s( l.begin() );
    ++s;
    l.splice( l.begin(), l, s );
    doPrint( l );

    return 0;
}


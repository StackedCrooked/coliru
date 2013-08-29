#include <iostream>

using namespace std;

template< typename T >
void Print(T V)
{
    std::cout << V << "\n";
}

template< typename T, typename... U >
void Print( T v, U... va )
{
    std::cout << v << " ";
    Print( va... );
}

/*
template< typename T >
T Acc( T v )
{
    return v;    
}
*/

template< typename T, typename... V >
T Acc( T v, V... va )
{
    if( sizeof...( va ) >= 1 )
        return v + Acc( va... );
    else
        return V
}

int main()
{
    Print( 2, 3, 4, 5 );
    Print( 2, 3, 4 );
    Print( 2, 3 );
    Print( 2 );
    
    Print( "Acc: " );
    Print( Acc(3.6, 5.4, 7.0, 8, 4.2) );
}

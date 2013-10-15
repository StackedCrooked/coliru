#include <iostream>

enum ENUM
{
    ONE     = 0x01,
    TWO     = 0x02,
    THREE   = 0x04,
    FOUR    = 0x08,
    FIVE    = 0x10,
    SIX     = 0x20
};

ENUM operator | ( ENUM lhs, ENUM rhs )
{
    // Cast to int first otherwise we'll just end up recursing
    return static_cast< ENUM >( static_cast< int >( lhs ) | static_cast< int >( rhs ) );
}

void enumTest( ENUM v )
{
    if ( v & ONE )
    {
        std::cout << "ONE ";
    }
    if ( v & TWO )
    {
        std::cout << "TWO ";
    }
    if ( v & THREE )
    {
        std::cout << "THREE ";
    }
    if ( v & FOUR )
    {
        std::cout << "FOUR ";
    }
    if ( v & FIVE )
    {
        std::cout << "FIVE ";
    }
    if ( v & SIX )
    {
        std::cout << "SIX";
    }
    
    std::cout << std::endl;
}

int main( int argc, char **argv )
{
    enumTest( ONE | TWO | FIVE );
    enumTest( TWO | THREE | FOUR | FIVE );
    enumTest( ONE | TWO | THREE | FOUR | FIVE | SIX );
    
    return 0;
}
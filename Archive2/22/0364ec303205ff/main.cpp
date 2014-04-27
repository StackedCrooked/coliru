#include <iostream>

struct string // belongs to the type category literal type
{
    constexpr explicit string( int v = 0 ) : value(v) {} 
    
    constexpr int size() const { return value ; } // size() is constexpr
    
    const int value ;    
};

constexpr bool isShorter( const string& s1, const string& s2 )
{
    return s1.size() < s2.size();
}

int main()
{
    constexpr char test [ isShorter( string(20), string(30) ) ? 100 : 200 ] = {0} ;
    std::cout << sizeof(test) << '\n' ;
}


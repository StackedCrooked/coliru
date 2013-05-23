#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <unordered_set>

const std::unordered_set<int> validOctalChars =
{
    '0', '1', '2', '3', '4', '5', '6', '7'
};

const std::unordered_set<int> validHexChars =
{
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'A', 'B', 'C', 'D', 'E', 'F'
};

bool validHexStr( std::string str, size_t end )
{
    //
    // Has to have at least three character 0x[0-9a-fA-F]
    //
    if( end <= 2 )
    {
        return false ;
    }
    
    if( str[0] != '0' ||
        (str[1] != 'x' && str[1] != 'X') )
    {
        return false ;
    }
    
    for( size_t i = 2; i < end; ++i )
    {
        if( 0 == validHexChars.count( str[i] ) )
        {
            return false ;
        }
    }
    
    return true ;
}

bool validOctalStr( std::string str, size_t end )
{
    if( str[0] != '0' )
    {
        return false ;
    }
    
    for( size_t i = 1; i < end; ++i )
    {
        if( 0 == validOctalChars.count( str[i] ) )
        {
            return false ;
        }
    }
    
    return true ;
}

bool isUserDefined( std::string str )
{
    return ( std::string::npos != str.find( '_' ) ) ;
}


int main()
{
    std::string intZero[] = { "0", "0x0", "00", "000000000000000000000000000" } ;
    
    std::cout << 0 << std::endl ;
    std::cout << 00 << std::endl ;
    std::cout << 0333 << std::endl ;
    std::cout << 333 << std::endl ;
    
    std::cout << validHexStr( intZero[1], 3 ) << std::endl ;
    std::cout << validHexStr( "0x0u_ud2", 4 ) << std::endl ;
    
    
    
    for( auto s : intZero )
    {
        /*
        long long tmpS ;
        unsigned long long tmpU ;
        
        bool isOct = false ;
        bool isHex = false ;
        */
        if( s[0] == '0' )
        {
            if( s.size() > 1 )
            {
                
            }
        }
        
        //tmp = 
        //std::cout << 
    }
}
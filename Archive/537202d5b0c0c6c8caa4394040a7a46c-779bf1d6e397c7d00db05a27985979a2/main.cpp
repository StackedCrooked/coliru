#include <iostream>
#include <limits>
#include <typeinfo>
#include <unordered_set>

const std::unordered_set<int> validOctalChars =
{
    '0', '1', '2', '3', '4', '5', '6', '7'
};

bool validOctalCharLiteral( std::string str, size_t start, size_t end )
{
    if( str[start] != '\\' )
    {
        return false ;
    }
    
    for( size_t i = start+1; i < end; ++i )
    {
        if( 0 == validOctalChars.count( str[i] ) )
        {
            return false ;
        }
    }
    
    return true ;
}

std::string extractOctalFromCharLiteral( std::string str, size_t start, size_t end )
{
    std::string tmp( "0" ) ;
    
    for( size_t i = start+1; i < end; ++i )
    {
        tmp += str[i] ;
    }
    
    return tmp ;
}

char ValueToHexChar(int c)
{
        switch (c)
        {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        case 10: return 'A';
        case 11: return 'B';
        case 12: return 'C';
        case 13: return 'D';
        case 14: return 'E';
        case 15: return 'F';
        default: throw std::logic_error("ValueToHexChar of nonhex value");
        }
}


std::string HexDump(const void* pdata, size_t nbytes)
{
        unsigned char* p = (unsigned char*) pdata;

        std::string s(nbytes*2, '?');

        for (size_t i = 0; i < nbytes; i++)
        {
                s[2*i+0] = ValueToHexChar((p[i] & 0xF0) >> 4);
                s[2*i+1] = ValueToHexChar((p[i] & 0x0F) >> 0);
        }

        return s;
}

int main()
{
    std::string octal1( "`\\101`" ) ;
    std::string octal2( "u`\\101`" ) ;
    
    std::cout << validOctalCharLiteral( octal1, 1, octal1.size()-1 ) <<  std::endl ;
    std::cout << validOctalCharLiteral( octal2, 2, octal1.size()-1 ) << std::endl ;
    
    int x ;
    
    std::string tmp ;
    
    tmp = extractOctalFromCharLiteral( octal1, 1, octal1.size()-1) ;
    
    x = std::strtol( tmp.c_str(), NULL, 8 ) ;
    
    tmp = HexDump( static_cast<void*>(&x), sizeof( x ) ) ;
    std::cout << tmp << std::endl ;
}
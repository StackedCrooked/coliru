#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <stdexcept>
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <unordered_set>

const int bigEndianCheck = 1;
#define is_bigendian() ( (*(char*)&bigEndianCheck) == 0 )

enum EFundamentalType
{
        // 3.9.1.2
        FT_SIGNED_CHAR,
        FT_SHORT_INT,
        FT_INT,
        FT_LONG_INT,
        FT_LONG_LONG_INT,

        // 3.9.1.3
        FT_UNSIGNED_CHAR,
        FT_UNSIGNED_SHORT_INT,
        FT_UNSIGNED_INT,
        FT_UNSIGNED_LONG_INT,
        FT_UNSIGNED_LONG_LONG_INT,

        // 3.9.1.1 / 3.9.1.5
        FT_WCHAR_T,
        FT_CHAR,
        FT_CHAR16_T,
        FT_CHAR32_T,

        // 3.9.1.6
        FT_BOOL,

        // 3.9.1.8
        FT_FLOAT,
        FT_DOUBLE,
        FT_LONG_DOUBLE,

        // 3.9.1.9
        FT_VOID,

        // 3.9.1.10
        FT_NULLPTR_T
};

const std::map<std::string, EFundamentalType> SuffixToFundamentalTypeMap
{
        {"l",FT_LONG_INT},
        {"L",FT_LONG_INT},

        {"ll", FT_LONG_LONG_INT},
        {"LL", FT_LONG_LONG_INT},

        {"u", FT_UNSIGNED_INT},
        {"U", FT_UNSIGNED_INT},

        {"ul", FT_UNSIGNED_LONG_INT},
        {"uL", FT_UNSIGNED_LONG_INT},
        {"UL", FT_UNSIGNED_LONG_INT},
        {"Ul", FT_UNSIGNED_LONG_INT},
        {"lu", FT_UNSIGNED_LONG_INT},
        {"Lu", FT_UNSIGNED_LONG_INT},
        {"LU", FT_UNSIGNED_LONG_INT},
        {"lU", FT_UNSIGNED_LONG_INT},

        {"ull", FT_UNSIGNED_LONG_LONG_INT},
        {"uLL", FT_UNSIGNED_LONG_LONG_INT},
        {"ULL", FT_UNSIGNED_LONG_LONG_INT},
        {"Ull", FT_UNSIGNED_LONG_LONG_INT},
        {"llu", FT_UNSIGNED_LONG_LONG_INT},
        {"LLu", FT_UNSIGNED_LONG_LONG_INT},
        {"LLU", FT_UNSIGNED_LONG_LONG_INT},
        {"llU", FT_UNSIGNED_LONG_LONG_INT},
        
        {"f", FT_FLOAT},
        {"F", FT_FLOAT},

} ;


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

bool validDigitStr( std::string str, size_t end )
{
    for( size_t i = 0; i < end; ++i )
    {
        if( !isdigit( str[i] ) )
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

bool isFloatingPointNumber( std::string str )
{
    size_t end = str.size() ;
    
    
    if( isUserDefined( str ) )
    {
        end = str.find( "_" ) ;
    }
    
    for( size_t i = 0; i < end; ++i )
    {
        if( '.' == str[i] ||
            'e' == tolower( str[i] ) )
        {
            return true ;
        }
    }
    
    return false ;
}

std::tuple<bool,std::string> isValidIntSuffix( std::string str )
{
    const size_t len = str.size() ;
    size_t start=0, suffixLen=0 ; 
    
    if( len >= 4 )
    {
        if( 'u' == std::tolower( str[len-3] ) || 'l' == std::tolower( str[len-3] ) )
        {
            start = len-3 ;
            suffixLen = 3 ;        
        }
        else if( 'u' == std::tolower( str[len-2] ) || 'l' == std::tolower( str[len-2] ) )
        {
            start = len-2 ;
            suffixLen = 2 ;        
        }
        else if( 'u' == std::tolower( str[len-1] ) || 'l' == std::tolower( str[len-1] ) )
        {
            start = len-1 ;
            suffixLen = 1 ;        
        }
    }
    else if( len == 3 )
    {
        if( 'u' == std::tolower( str[1] ) || 'l' == std::tolower( str[1] ) )
        {
            start = 1 ;
            suffixLen = 2 ;        
        }
        else if( 'u' == std::tolower( str[2] ) || 'l' == std::tolower( str[2] ) )
        {
            start = 2 ;
            suffixLen = 1 ;        
        }
        
        
    }
    else if( len == 2 )
    {
        if( 'u' == std::tolower( str[1] ) || 'l' == std::tolower( str[1] ) )
        {
            start = 1 ;
            suffixLen = 1 ;        
        }
    }

    if( 0 != SuffixToFundamentalTypeMap.count( str.substr( start, suffixLen ) ) )
    {
        return std::make_tuple( true, str.substr( start, suffixLen ) ) ;
    }

    return std::make_tuple( false, "" ) ;
}

std::tuple<bool,std::string> isValidFloatSuffix( std::string str )
{
    const size_t len = str.size() ;
    
    if( 'f' == std::tolower( str[len-1] ) )
    {
        return std::make_tuple( true, str.substr( len-1, 1 ) ) ;
    }
    
    return std::make_tuple( false, "" ) ;
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

void SwapBytes(void *pv, size_t n)
{
    char *p = static_cast<char*>( pv );
    size_t lo, hi;
    for(lo=0, hi=n-1; hi>lo; lo++, hi--)
    {
        char tmp=p[lo];
        p[lo] = p[hi];
        p[hi] = tmp;
    }
} 

std::string getSuffixForIntType( unsigned long long val )
{
    long long tmpll = val ;
    std::string suffix("") ;
    
    std::cout <<  " tmpll: " << tmpll << std::endl ;
                    
    if( tmpll >= std::numeric_limits<int>::lowest() &&
            tmpll <= std::numeric_limits<int>::max() )
    {
        // no op no suffix needed
        std::cout <<"is a int" << std::endl ;
        
        int x = static_cast<int>( tmpll ) ;
        std::string tmp = HexDump( &x, sizeof( x ) ) ;
        std::cout << tmp << std::endl ;
    }
    else if( tmpll >= std::numeric_limits<long>::lowest() &&
        tmpll <= std::numeric_limits<long>::max() )
    {
        suffix = "l" ;
        std::cout << " is a long" << std::endl ;
        
        long x = static_cast<long>( tmpll ) ;
        std::string tmp = HexDump( &x, sizeof( x ) ) ;
        std::cout << tmp << std::endl ;
    }
    else if( tmpll >= std::numeric_limits<long long>::lowest() &&
        tmpll <= std::numeric_limits<long long>::max() )
    {
        suffix = "ll" ;
        std::cout <<" is a long long" << std::endl ;
    }
    
    return suffix ;
}

int main()
{  
    std::cout << is_bigendian()<< std::endl ;
    int x = 0x123 ;
    int x2 = x ;
    SwapBytes( &x2, sizeof(x2) ) ;
    std::string tmp = HexDump( &x, sizeof( x ) ) ;
    
    
    std::cout << tmp << std::endl ;
    tmp = HexDump( static_cast<void*>(&x2), sizeof( x2 ) ) ;
    std::cout << tmp << std::endl ;
    
    /*
    std::string intZero[] = { "0", "0x0", "00", "000000000000000000000000000" } ;
    std::string others[] = { "0Ull", "0Ul", "0u" } ;
    std::string userDef[] = { "0x0_hex", "010101_bin", "0u_num" } ;
    */
    std::string mixed[] = { "0x0_hex", "010101_bin", "20", "0x25", "2147483647", "2147483648", "9223372036854775800", "0u_num", "20u", "100ull", "2147483647Ul", "18446744073709551615Ull", "0X", "0lL", "0x0Wll", "0.0", "0e1" } ;
    
    /*
    auto suffixT = isValidIntSuffix( others[0] ) ;    
    std::cout << std::get<0>( suffixT ) << ":" << std::get<1>(suffixT) << std::endl ;
    suffixT = isValidIntSuffix( others[1] ) ;    
    std::cout << std::get<0>( suffixT ) << ":" << std::get<1>(suffixT) << std::endl ;
    suffixT = isValidIntSuffix( others[2] ) ;    
    std::cout << std::get<0>( suffixT ) << ":" << std::get<1>(suffixT) << std::endl ;
    
    std::cout << 0 << std::endl ;
    std::cout << 00 << std::endl ;
    std::cout << 0333 << std::endl ;
    std::cout << 333 << std::endl ;
    
    std::cout << validHexStr( intZero[1], 3 ) << std::endl ;
    std::cout << validHexStr( "0x0u_ud2", 4 ) << std::endl ;
    std::cout << isUserDefined( "0x0u_ud2" ) << std::endl ;
    
    auto suffixT = isValidFloatSuffix( "42.421e20" ) ;    
    std::cout << std::get<0>( suffixT ) << ":" << std::get<1>(suffixT) << std::endl ;
    */
    
        std::cout << "type\tlowest\thighest\n";
    std::cout << "int\t"
              << std::numeric_limits<int>::lowest() << '\t'
              << std::numeric_limits<int>::max() << '\n';
    std::cout << "long\t"
              << std::numeric_limits<long>::lowest() << '\t'
              << std::numeric_limits<long>::max() << '\n';
    std::cout << "long long\t"
              << std::numeric_limits<long long>::lowest() << '\t'
              << std::numeric_limits<long long>::max() << '\n';

    
    for( auto s : mixed )
    {
        if( isFloatingPointNumber( s ) )
        {
            std::cout << "Floating point: " << s << std::endl ;   
        }
        else
        {        
            if( isUserDefined( s ) )
            {
                size_t underPos = s.find( "_" ) ;
                
                bool
                    isHex   = validHexStr( s, underPos ),
                    isOctal = validOctalStr( s, underPos ) ;
            
                std::cout << "uderPos: " << underPos << std::endl ;
            
                if( !isHex &&
                    !isOctal &&
                    !validDigitStr( s, underPos ) )
                {
                    std::cout << "uderdefined literal not valid: " << s << std::endl ;
                }
            }
            else
            {
                auto suffixT = isValidIntSuffix( s ) ;
                std::string suffix("") ;
                size_t end = s.size() ;
                unsigned long long tmpull ;
            
                if( std::get<0>( suffixT ) )
                {
                    end = end - std::get<1>( suffixT ).size() ;
                
                    std::cout << s << " new end: " << end << std::endl ;
                    suffix = std::get<1>( suffixT ) ;
                }
                
                bool
                    isHex = validHexStr( s, end ) ,
                    isOctal = validOctalStr( s, end ) ;
            
                if( !isHex &&
                    !isOctal &&
                    !validDigitStr( s, end ) )
                {
                    std::cout << "literal not valid: " << s << std::endl ;
                    continue ;
                }
                
                int base = 10 ;
                
                if( isHex ) 
                {
                    base = 16 ;
                }
                else if( isOctal )
                {
                    base = 8 ;
                }
                
                tmpull = std::strtoull( s.c_str(), NULL, base ) ;
                
                std::cout << "s: " << s << " tmpull: " << tmpull << std::endl ;
                
                if( !std::get<0>( suffixT ) )
                {
                    suffix = getSuffixForIntType( tmpull ) ;    
                }
            }
        }
    }
}
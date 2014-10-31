#include <iostream>
#include <iomanip>
#include <limits>
#include <bitset>
#include <string>

int scoutsNumber( unsigned int num )
{
    // static constexpr int weridNum[]= {64, 128, 256, 512, 1021, 2048, 4096, 8192, 16384, 32768, 65536};
	return num == 4 ? 1021 : 1u << (num+6) ;
}

std::string pretty_string( std::string str )
{
    if( str.empty() ) return "" ;

    std::string pretty( 1, str.front() ) ;
    for( std::size_t i = 1 ; i < str.size() ; ++i )
    {
        pretty += str[i] ;
        if( i%4 == 3 ) pretty += ' ' ;
    }

    return pretty ;
}

constexpr int digits = std::numeric_limits<unsigned int>::digits ;

std::string to_bin( int n ) { return pretty_string( std::bitset<digits>(n).to_string() ) ; }

int main()
{

    const auto dec = [] ( std::ostream& stm ) -> std::ostream& { return stm << std::dec << std::setw( std::numeric_limits<int>::digits10 + 3 ) ; };
    const auto oct = [] ( std::ostream& stm ) -> std::ostream& { return stm << std::oct << std::setw( (digits+2) / 3 + 2 ) ; };
    const auto hex = [] ( std::ostream& stm ) -> std::ostream& { return stm << std::hex << std::setw( (digits+3) / 4 + 2 ) ; };
    const auto bin = [] ( std::ostream& stm ) -> std::ostream& { return stm << std::setw( to_bin(0).size() + 5 ) ; };

    //std::cout << std::showbase ;
    for( int i = 0 ; i < 11 ; ++i )
    {
        const int n0 = scoutsNumber(i);
        for( int j : { -1, 0, 1 } )
        {
            const int n = n0 + j ;
            std::cout << dec << n << oct << n << hex << n << bin << to_bin(n) << '\n' ;
        }
    }
}

#include <iostream>
#include <string>
#include <iomanip>

bool is_binary_string( std::string str )
{
    // if any character other than '0' or '1' is present, it is not a binary string
    for( char c : str ) if( c != '0' && c != '1' ) return false ;

    return true ;
}

std::string to_binary_string( unsigned long long n )
{
    if( n == 0 ) return "" ;

    else return to_binary_string(n/2) + ( (n%2) ? '1' : '0' ) ;
    // to_binary_string(29) == to_binary_string(14) + '1'
    // to_binary_string(28) == to_binary_string(14) + '0'
}

unsigned long long to_number( std::string binary_str )
{
    if( binary_str.empty() || !is_binary_string(binary_str) ) return 0 ;

    // first n-1 binary digits
    const std::string head( binary_str.begin(), binary_str.end() - 1 ) ; //
    const char tail = binary_str.back() ; // last char

    // to_numer( "100101" ) == to_numer( "10010" /*head*/ ) * 2 + ( 1 /*tail*/ )
    // to_numer( "100100" ) == to_numer( "10010" /*head*/ ) * 2 + ( 0 /*tail*/ )
    return to_number(head) * 2 + ( tail == '1' ) ;
}

std::string xor_binary_strings( std::string a, std::string b )
{
    if( !is_binary_string(a) || !is_binary_string(b) ) return "" ;

    // make the strings of the same size (pad zeroes on the left)
    while( a.size() < b.size() ) a = '0' + a ;
    while( b.size() < a.size() ) b = '0' + b ;

    std::string xor_result ;
    for( std::size_t i = 0 ; i < a.size() ; ++i )
        xor_result += a[i] == b[i] ? '0' : '1' ; // '0' if same, '1' if different

    return xor_result ;
}

int main() // minimal test driver
{
    const unsigned long long n = 123456789012345 ;
    std::cout << n << '\n'
               << to_binary_string(n) << '\n'
               << to_number( to_binary_string(n) )
               << "\n----------------------------\n" ;

    const std::string binary = "110111100000010100011000101110101111101101101110111000110100" ;
    std::cout << binary << '\n'
               << to_number(binary) << '\n'
               << to_binary_string( to_number(binary) )
               << "\n----------------------------\n" ;

    const std::string a = "1100110011001100110011001100110011001100" ;
    const std::string b = "101010101010101010101010101010101010101010101010" ;
    std::cout << std::setw(50) << a << '\n'
               << std::setw(50) << b << '\n'
               << std::setw(50) << xor_binary_strings(a,b) << '\n'
               << to_number(a) << '\n'
               << to_number(b) << '\n'
               << ( to_number(a) ^ to_number(b) ) << '\n'
               << to_number( xor_binary_strings(a,b) ) << '\n' ;
}

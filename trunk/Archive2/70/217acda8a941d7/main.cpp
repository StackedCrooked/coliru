#include <iostream>
#include <bitset>  // **** <bits/stdc++.h> is not a standard header
#include <limits>
#include <string>

int main()
{
    // numbr of bnary digits in unsigned int
    const std::size_t NBITS = std::numeric_limits< unsigned int >::digits ;

    unsigned int n ;
    std::cin >> n ;
    
    std::cout << "decimal: " << n << "  binary: " ;
    const std::bitset<NBITS> bits(n) ;

    const std::string str_bits = bits.to_string() ; // convert to a string of zeroes and ones
    const auto first_digit = str_bits.find('1') ; // locate the first '1'

    if( first_digit != std::string::npos ) std::cout << str_bits.substr(first_digit) << '\n' ;
    else std::cout << "0\n" ; // all the bits were zeroes
}

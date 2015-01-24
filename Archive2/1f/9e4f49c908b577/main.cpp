#include <iostream>
#include <bitset>  // **** <bits/stdc++.h> is not a standard header
#include <limits>
#include <string>

int main()
{
    // numbr of bnary digits in unsigned int
    // http://en.cppreference.com/w/cpp/types/numeric_limits/digits
    const std::size_t NBITS = std::numeric_limits< unsigned int >::digits ;

    unsigned int n ;
    std::cin >> n ;
    
    std::cout << "decimal: " << n << "  binary: " ;
    const std::bitset<NBITS> bits(n) ;

    const std::string str_bits = bits.to_string() ; // convert to a string of zeroes and ones
    
    // http://en.cppreference.com/w/cpp/string/basic_string/find
    const auto first_digit = str_bits.find('1') ; // locate the first '1'

    if( first_digit != std::string::npos ) // found it; print the substring starting at the first '1'
        std::cout << str_bits.substr(first_digit) << '\n' ; // http://en.cppreference.com/w/cpp/string/basic_string/substr
        
    else std::cout << "0\n" ; // all the bits were zeroes
}

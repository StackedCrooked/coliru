#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>
#include <type_traits>
#include <iostream>

template < std::size_t BASE, 
           typename DIGIT = typename std::conditional< BASE <= ( std::numeric_limits<unsigned char>::max() + 1 ), unsigned char, std::uint16_t >::type > 
std::vector<DIGIT> to_base( const std::string& unsigned_decimal )
{
    static_assert( BASE > 1 && BASE <= ( std::numeric_limits<DIGIT>::max() + 1 ), "" ) ;
    std::vector<DIGIT> result ;
    
    boost::multiprecision::cpp_int number(unsigned_decimal) ;
    while( number != 0 ) 
    {
        // std::cout << number << '\n' ;
        const boost::multiprecision::cpp_int digit = number % BASE ;
        result.push_back( digit.convert_to<DIGIT>() ) ;
        number /= BASE ;
    }
    
    std::cout << std::dec << "\n\n" << result.size() << " digits to base " << BASE << " == " 
              << result.size() * sizeof(DIGIT) << " bytes\n" ;
    return result ;
}

int main()
{
    const std::string number =  "1234565789012345657890123456578901234565789012345657890123456578901234565789012345657890"
                                "1234565789012345657890123456578901234565789012345657890123456578901234565789012345657890" 
                                "1234565789012345657890123456578901234565789012345657890123456578901234565789012345657890" 
                                "1234565789012345657890123456578901234565789012345657890123456578901234565789012345657890" 
                                "1234565789012345657890123456578901234565789012345657890123456578901234565789012345657890" ;
                                
    for( auto code_point : to_base<64>(number)  ) std::cout << std::hex << int(code_point) << ' ' ;
    for( auto code_point : to_base<256>(number)  ) std::cout << std::hex << int(code_point) << ' ' ;
    for( auto code_point : to_base<65536>(number)  ) std::cout << std::hex << int(code_point) << ' ' ;
}

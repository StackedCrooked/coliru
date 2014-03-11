#include <iostream>
#include <string>
#include <boost/regex.hpp>

int main()
{
    const std::string test_cases[] = { "12-22", "+12 / 22", "+12345 * -32768", "+12*-0", "01 * 22", "123 **34", "+0++0" } ;
    
    const std::string zero_or_more_ws = R"(\s*)" ;  
    const std::string optional_sign = R"([+\-]?)" ;
    const std::string integer  = "(0|[1-9][0-9]*)" ; 
    const std::string oper = R"([+\-*/])" ;
    const std::string number = optional_sign + integer ;
    
    const boost::regex expression( '^' + number + zero_or_more_ws + oper  + zero_or_more_ws + number + '$' ) ; 
    const boost::regex ditto( R"(^[+\-]?(0|[1-9][0-9]*)\s*[+\-*/]\s*[+\-]?(0|[1-9][0-9]*)$)" ) ;  

    for( std::string s : test_cases )
    {
        std::cout << s << " -> " << std::boolalpha << boost::regex_match( s, expression ) 
                  << " (" << boost::regex_match( s, ditto ) << ")\n" ;
    }
}

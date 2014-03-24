#include <iostream>
#include <sstream>

int main()
{
    // right at the beginning

    // http://www.cplusplus.com/reference/sstream/stringbuf/stringbuf/
    std::stringbuf sbuf( std::ios_base::out ) ;
    // http://www.cplusplus.com/reference/ios/ios/rdbuf/
    const auto old_buf = std::cout.rdbuf(&sbuf) ;

    // in the rest of the program, use cout as it is being used right now

    std::cout << "hello world " << 12345 << ' ' << '$' ; // for example

    // finally, at the end

    std::cout.rdbuf(old_buf) ;
    // http://www.cplusplus.com/reference/sstream/stringbuf/str/
    const std::string text_out = sbuf.str() ;
    std::cout << "string text_out contains: " << text_out << '\n' ;
}

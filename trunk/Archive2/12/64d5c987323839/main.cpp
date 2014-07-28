#include <iostream>
#include <iterator>
#include <string>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

int main() {
    using namespace boost::spirit;
    using boost::phoenix::ref;
    std::string s{"#F0E5B1"};
    
    int r{}, g{}, b{};
    
    qi::int_parser<unsigned char, 16, 2, 2> hex_byte;
    
    auto first = std::begin(s), last = std::end(s);
    qi::phrase_parse(first, last,
        ('#' >> hex_byte[ref(r) = qi::_1] >> hex_byte[ref(g) = qi::_1] >> hex_byte[ref(b) = qi::_1]),
        ascii::space
    );
        
    std::cout << std::hex << r << ' ' << g << ' ' << b;   
}
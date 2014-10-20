#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <string>
#include <algorithm>

namespace client {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    
    template <typename Iterator>
    struct gram : qi::grammar<Iterator, std::string(), ascii::space_type> {
        gram() : gram::base_type(start) {    
            start %= "'" >> *(string_char) >> "'";
            string_char = ("\\" >> qi::char_('\'')) | 
                          ("\\x" >> qi::hex)        |
                          (qi::print - "'");
        }    
        qi::rule<Iterator, std::string(), ascii::space_type> string_char, start;
    };
}

int main() {
    namespace qi = boost::spirit::qi;
    
    client::gram<const char*> gr;
    std::string result;
    
    char const *first = "'a\\'bc\\x30gh'", *last = first + std::strlen(first);
    bool success = qi::phrase_parse(first, last, gr, boost::spirit::ascii::space, result);

    if(!success)
        std::cout << "Syntax error at: " << std::distance(first, last);
    else
        std::cout << result << std::endl;
        
    return 0;
}

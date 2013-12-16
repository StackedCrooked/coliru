#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>

namespace spirit = boost::spirit;
namespace qi = boost::spirit::qi;
namespace phoenix = boost::phoenix;


int main() {

    std::string input("1 2");

    qi::rule<std::string::iterator, void(), qi::space_type> parser;
    qi::rule<std::string::iterator, void(), qi::space_type> parser2;
    qi::rule<std::string::iterator, void(), qi::space_type> parser3;

    parser = qi::int_[
        std::cerr << phoenix::val("First int: ") << qi::_1 << std::endl
    ];

    parser2 = qi::int_[
        std::cerr << phoenix::val("Second int: ") << qi::_1 << std::endl
    ];

    try {
        // Comment out these two lines, (finished below ...)
        parser3 = parser >> parser2;
        phrase_parse(input.begin(), input.end(), parser3, qi::space);

        parser = parser.copy() >> parser2;
        phrase_parse(input.begin(), input.end(), parser, qi::space);
    }
    catch (...) {
        std::cerr << "Exception caught." << std::endl;
    }

} 

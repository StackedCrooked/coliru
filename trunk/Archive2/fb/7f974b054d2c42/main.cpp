#define BOOST_RESULT_OF_USE_DECLTYPE
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <string>
#include <iostream>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;
namespace spirit = boost::spirit;
namespace phoenix = boost::phoenix;

int main() {

    std::string input{"test1 test2 test3 FOO!"};
    typedef decltype(input.begin()) StringIter;

    qi::rule<StringIter, std::string()> parser =
        *(
            qi::char_
            [
                phoenix::bind(
                    [] (char value) {
                        std::cerr << value << std::endl;
                    },
                    qi::_1
                )
            ]
        );

    qi::parse(input.begin(), input.end(), parser);
}

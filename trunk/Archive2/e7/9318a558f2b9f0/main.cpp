#include <string>
#include <iostream>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;
namespace spirit = boost::spirit;

using namespace boost::phoenix;

int main() {

    std::string input{"test1 test2 test3 FOO!"};
    typedef decltype(input.begin()) StringIter;

    char c = 'a';
    qi::rule<StringIter, std::string()> parser =
        *(
            qi::char_
            [
                ref(c) = qi::_1
            ]
        );

    qi::parse(input.begin(), input.end(), parser);
    std::cout << c << std::endl;
}

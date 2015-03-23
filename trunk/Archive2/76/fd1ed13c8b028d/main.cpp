#include <iostream>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;

int main() {
    std::ostreambuf_iterator<char> out(std::cout);

    qi::symbols<char, char> lookup_table;
    lookup_table.add
        ("0000", '0')
        ("0001", '1')
        ("0010", '2')
        ("0011", '3')
        ("0100", '4')
        ("0101", '5')
        ("0110", '6')
        ("0111", '7')
        ("1000", '8')
        ("1001", '9')
        ("1010", 'a')
        ("1011", 'b')
        ("1100", 'c')
        ("1101", 'd')
        ("1110", 'e')
        ("1111", 'f')
        ;

    boost::spirit::istream_iterator bof(std::cin), eof;

    if (qi::parse(bof, eof, +lookup_table [ *boost::phoenix::ref(out) = qi::_1 ]))
        return 0;
    else
        return 255;
}

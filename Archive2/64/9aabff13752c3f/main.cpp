#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include <iostream>
#include <fstream>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

template <typename Iterator>
struct roman : qi::grammar<Iterator>
{
    roman() : roman::base_type(start)
    {
        using namespace qi;

        start = eps > +lit('M') >> "</>";
        start.name("start");

        on_error<fail>(start, 
                phx::ref(std::cout)
                   << "Error! Expecting "
                   << qi::_4
                   << " here: '"
                   << phx::construct<std::string>(qi::_3, qi::_2)
                   << "'\n"
            );
    }
    qi::rule<Iterator> start;
};

int main()
{
    typedef std::string::const_iterator iterator_type;
    roman<iterator_type> roman_parser; // Our grammar

    std::string str;
    while (std::getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

        iterator_type iter = str.begin(), end = str.end();
        unsigned result;
        bool r = parse(iter, end, roman_parser, result);

        if (r && iter == end)
        {
            std::cout << "Parsing succeeded\n";
            std::cout << "result = " << result << std::endl;
        }
        else
        {
            std::string rest(iter, end);
            std::cout << "Parsing failed\n";
            std::cout << "stopped at: '" << rest << "'\n";
        }
    }
}

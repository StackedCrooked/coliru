#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <iostream>
#include <string>

using namespace std;
namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct keyword_parser : qi::grammar<Iterator, ascii::space_type>
{
    struct mySymbols_ : qi::symbols<char, unsigned>
    {
        mySymbols_()
        {
            add
            ("ONE"   , 1)
            ("TWO"   , 2)
            ("THREE" , 2)
            ;
        }

    } mySymbols;

    keyword_parser() : keyword_parser::base_type(start)
    {
        using qi::_1;
        using ascii::char_;
        using phx::val;

        start %= *(
                   keyword  [cout << val("Keyword as a number: ") << _1 << endl]
                 | invalid  [cout << val("Invalid keyword: ")     << _1 << endl]
                 );

        keyword = mySymbols >> !(char_("a-zA-Z0-9_"));

        invalid = +ascii::graph;
    }

    qi::rule<Iterator, ascii::space_type> start;
    // lexemes do not ignore embedded skippables
    qi::rule<Iterator, int()> keyword;
    qi::rule<Iterator, std::string()/*IMPLICIT LEXEME:, ascii::space_type*/> invalid;
};

int main()
{
    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;
    typedef keyword_parser<iterator_type> keyword_parser;

    std::string s = "ONE TWO ONEMORE THREE";
    iterator_type b = s.begin();
    iterator_type e = s.end();
    phrase_parse(b, e, keyword_parser(), space);

    return 0;
}

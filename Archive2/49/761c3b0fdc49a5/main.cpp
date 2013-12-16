#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;

struct T3_Command
{
    bool add_command(int i, std::string const& s) 
    {
        std::cout << "adding command [" << i << ", " << s << "]\n";
        return i != 42; // just to show how you can do input validation
    }
};

template <typename Iterator>
struct roster_grammar : qi::grammar<Iterator, T3_Command(), qi::space_type>
{   
    roster_grammar() : 
        roster_grammar::base_type(start_)
    {
        start_   = *(qi::int_ >> string_p) 
            [qi::_pass = phx::bind(&T3_Command::add_command, qi::_val, qi::_1, qi::_2)];

        string_p = qi::lexeme[+(qi::graph)];
    }

    qi::rule <Iterator, T3_Command(), qi::space_type> start_;
    qi::rule <Iterator, std::string()> string_p;
};

int main()
{
    typedef boost::spirit::istream_iterator iter_type;
    typedef roster_grammar<iter_type> student_p;
    student_p my_parser;

    //open the target file and wrap istream into the iterator
    std::cin.unsetf(std::ios::skipws);//Disable Whitespace Skipping
    iter_type begin(std::cin);
    iter_type end;

    using boost::spirit::qi::space;
    using boost::spirit::qi::phrase_parse;
    bool r = phrase_parse(begin, end, my_parser, space);

    if (r)
        std::cout << "parse (partial) success\n";
    else      
        std::cerr << "parse failed: '" << std::string(begin,end) << "'\n";
    if (begin!=end) 
        std::cerr << "trailing unparsed: '" << std::string(begin,end) << "'\n";

    return r?0:255;
}

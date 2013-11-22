#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi    = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phx   = boost::phoenix;

template <typename StreamIterator, typename CharType=char>
struct json_start_elem_grammar_object : qi::grammar<StreamIterator,
    void(const CharType*, CharType),
    ascii::blank_type>
{
    json_start_elem_grammar_object() : json_start_elem_grammar_object::base_type(start_elem, "start_elem")
    {
        using namespace qi;
        auto name     = lit(_r1);
        auto preamble = lit(_r2);

        start_elem = 
            '"' > name > '"' > 
            ':' > preamble > 
            -lit('\n')
            ;
    }

    qi::rule<StreamIterator, void(const CharType*, CharType), ascii::blank_type>  start_elem;
};

bool doParse(const std::string& input)
{
    typedef std::string::const_iterator It;
    auto f(begin(input)), l(end(input));

    json_start_elem_grammar_object<It> p;

    try
    {
        bool ok = qi::phrase_parse(f, l, p(+"lol", 'q'), ascii::blank);
        if (ok)   
        {
            std::cout << "parse success\n";
        }
        else      std::cerr << "parse failed: '" << std::string(f,l) << "'\n";

        if (f!=l) std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";
        return ok;
    } catch(const qi::expectation_failure<It>& e)
    {
        std::string frag(e.first, e.last);
        std::cerr << e.what() << "'" << frag << "'\n";
    }

    return false;
}

int main()
{
    bool ok = doParse("\"lol\" : q\n");
    return ok? 0 : 255;
}

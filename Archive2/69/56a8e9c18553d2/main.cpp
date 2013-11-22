#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/repository/include/qi_distinct.hpp>
#include <boost/spirit/include/karma.hpp>

namespace qi    = boost::spirit::qi;
namespace karma = boost::spirit::karma;
namespace phx   = boost::phoenix;

typedef std::vector<int> attr_t;

///////////////////////////////////////////////////////////////////////////////
namespace distinct
{
    //[qi_distinct_encapsulation
    namespace spirit = boost::spirit;
    namespace ascii = boost::spirit::ascii;
    namespace repo = boost::spirit::repository;

    // Define metafunctions allowing to compute the type of the distinct()
    // and ascii::char_() constructs
    namespace traits
    {
        // Metafunction allowing to get the type of any repository::distinct(...) 
        // construct
        template <typename Tail>
        struct distinct_spec
          : spirit::result_of::terminal<repo::tag::distinct(Tail)>
        {};

        // Metafunction allowing to get the type of any ascii::char_(...) construct
        template <typename String>
        struct char_spec
          : spirit::result_of::terminal<spirit::tag::ascii::char_(String)>
        {};
    }

    // Define a helper function allowing to create a distinct() construct from 
    // an arbitrary tail parser
    template <typename Tail>
    inline typename traits::distinct_spec<Tail>::type
    distinct_spec(Tail const& tail)
    {
        return repo::distinct(tail);
    }

    // Define a helper function allowing to create a ascii::char_() construct 
    // from an arbitrary string representation
    template <typename String>
    inline typename traits::char_spec<String>::type
    char_spec(String const& str)
    {
        return ascii::char_(str);
    }

    // the following constructs the type of a distinct_spec holding a
    // charset("0-9a-zA-Z_") as its tail parser
    typedef traits::char_spec<std::string>::type charset_tag_type;
    typedef traits::distinct_spec<charset_tag_type>::type keyword_tag_type;

    // Define a new Qi 'keyword' directive usable as a shortcut for a
    // repository::distinct(char_(std::string("0-9a-zA-Z_")))
    std::string const keyword_spec("0-9a-zA-Z_");
    keyword_tag_type const keyword = distinct_spec(char_spec(keyword_spec)); 
    //]
}
template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, attr_t(), Skipper>
{
    parser() : parser::base_type(start)
    {
        using namespace qi;

        syms.add 
            ("one", 1)
            ("two", 2)
            ("three", 3);

        start = *(distinct::keyword[syms] | qi::omit[ qi::lexeme[+qi::graph] ]);
    }

  private:
    qi::symbols<char, int> syms;
    qi::rule<It, attr_t(), Skipper> start;
};

bool doParse(const std::string& input)
{
    typedef std::string::const_iterator It;
    auto f(begin(input)), l(end(input));

    parser<It, qi::space_type> p;
    attr_t data;

    try
    {
        bool ok = qi::phrase_parse(f,l,p,qi::space,data);
        if (ok)   
        {
            std::cout << "parse success\n";
            std::cout << "data: " << karma::format_delimited(karma::auto_, ' ', data) << "\n";
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
    bool ok = doParse("one in three men are overweight");
    return ok? 0 : 255;
}

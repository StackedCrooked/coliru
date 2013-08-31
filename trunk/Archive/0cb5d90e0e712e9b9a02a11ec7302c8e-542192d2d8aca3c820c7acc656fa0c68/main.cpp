#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>
// #include <boost/spirit/include/phoenix.hpp>

namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;

typedef std::string column_name_t;

enum sql_faggregate
{
    SUM,
    // ....
    AVG,
};

typedef std::pair<column_name_t, sql_faggregate> column_and_aggregate;
typedef std::vector<column_and_aggregate> column_and_aggregate_container;

template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, column_and_aggregate_container(), Skipper>
{
    parser() : parser::base_type(aggregates_parser)
    {
        using namespace qi;
        // using phx::bind; using phx::ref; using phx::val;

        quoted_string = lexeme [ "'" >> *~qi::char_("'") >> "'" ];
        faggr = int_;
        agg_pair = quoted_string > ':' > faggr;
        aggregates_parser = '{' > agg_pair % ',' > '}';
        
        BOOST_SPIRIT_DEBUG_NODE(aggregates_parser);
    }

  private:
    qi::rule<It, std::string(), qi::space_type>           quoted_string;
    qi::rule<It, sql_faggregate(), qi::space_type>        faggr;
    qi::rule<It, column_and_aggregate(), qi::space_type>           agg_pair;
    qi::rule<It, column_and_aggregate_container(), qi::space_type> aggregates_parser;
};

bool doParse(const std::string& input)
{
    typedef std::string::const_iterator It;
    auto f(begin(input)), l(end(input));

    parser<It, qi::space_type> p;
    column_and_aggregate_container data;

    try
    {
        bool ok = qi::phrase_parse(f,l,p,qi::space,data);
        if (ok)   
        {
            std::cout << "parse success\n";
            for (auto& pair : data)
                std::cout << "result: '" << pair.first << "' : " << (int) pair.second << "\n";
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
    bool ok = doParse("{ 'column 1' : 1, 'column 2' : 0, 'column 3' : 1 }");
    return ok? 0 : 255;
}

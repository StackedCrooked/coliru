//#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

struct Definition {
    std::string name;
    boost::optional<std::string> value;
};

BOOST_FUSION_ADAPT_STRUCT(Definition, (std::string, name)(boost::optional<std::string>, value))

using Definitions = std::vector<Definition>;

template <typename Iterator, typename Skipper = qi::space_type>
struct grammar : qi::grammar<Iterator, Definitions(), Skipper>
{
    grammar() : grammar::base_type(start) {
        using namespace qi;

        op         = char_("-+/*");

        name       = +(graph - '=' - op);

        simple     = +(graph - op);

        expression = raw [
                '(' >> expression >> ')'
              | simple >> *(op >> expression)
              ];

        value      = expression;

        definition = name >> - ('=' > value);
        start      = *definition;

        BOOST_SPIRIT_DEBUG_NODES((simple)(value)(expression)(name)(definition)(start))
    }
  private:
    qi::rule<Iterator> simple;
    qi::rule<Iterator, char()> op;
    qi::rule<Iterator, std::string()/*no skipper*/> name;
    qi::rule<Iterator, std::string(), Skipper> expression, value;
    qi::rule<Iterator, Definition(),  Skipper> definition;
    qi::rule<Iterator, Definitions(), Skipper> start;
};

int main()
{
    using It = std::string::const_iterator;
    std::string const input = "p1 p2 =   (v21 +  v22)   p3=v31-v32    p4  p5=v5";
    It f(input.begin()), l(input.end());

    Definitions defs;
    if (qi::phrase_parse(f, l, grammar<It>(), qi::space, defs))
    {
        std::cout << "Parsed " << defs.size() << " definitions\n";
        for (auto const& def : defs)
        {
            std::cout << def.name;
            if (def.value)
                std::cout << " with value expression '" << *def.value << "'\n";
            else
                std::cout << " with no value expression\n";
        }
    } else
    {
        std::cout << "Parse failed\n";
    }

    if (f != l)
        std::cout << "Remaining unparsed input: '" << std::string(f,l) << "'\n";
}

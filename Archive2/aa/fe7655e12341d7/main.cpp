#define BOOST_SPIRIT_USE_PHOENIX_V3
//#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace client {
    namespace spirit = boost::spirit;
    namespace qi     = boost::spirit::qi;
    namespace phx    = boost::phoenix;
    namespace ascii  = boost::spirit::ascii;

    struct summand {
        float factor;
        std::string name;

        summand() : factor(1.f), name("") {}
    };
}

namespace client {

    template <typename Iterator>
    struct summand_parser : qi::grammar<Iterator, summand(), ascii::space_type>
    {
        summand_parser() : summand_parser::base_type(summand_rule)
        {
            using namespace ascii;

            static const auto _factor = phx::bind(&summand::factor, qi::_r1);
            static const auto _name   = phx::bind(&summand::name,   qi::_r1);

            name_rule   = qi::as_string [ '[' >> qi::lexeme[alpha >> *alnum] >> ']' ] 
                                          [ _name   = qi::_1 ] ;
            factor_rule = qi::double_     [ _factor = qi::_1 ] ;

            summand_rule = 
                      factor_rule (qi::_val) >> - ( -qi::lit('*') >> name_rule   (qi::_val) )
                    | name_rule   (qi::_val) >> - ( -qi::lit('*') >> factor_rule (qi::_val) )
                ;

            BOOST_SPIRIT_DEBUG_NODES((summand_rule)(name_rule)(factor_rule))
        }

        qi::rule<Iterator, void(summand&), ascii::space_type> name_rule, factor_rule;
        qi::rule<Iterator, summand(),      ascii::space_type> summand_rule;
    };
}

bool parseSummandsInto(std::string const& str, client::summand& summand)
{
    typedef std::string::const_iterator It;
    static const client::summand_parser<It> g;

    It iter(str.begin()), end(str.end());
    bool r = phrase_parse(iter, end, g, boost::spirit::ascii::space, summand);

    return (r && iter == end);
}

int main()
{
    std::vector<std::string> inputStrings = {
        "7.5*[someAlphanumStr]",
        "7.5[someAlphanumStr]",
        "[someAlphanumStr]*7.4",
        "[someAlphanumStr]5",
        "7.4",
        "[someAlphanumStr]",
    };

    std::for_each(inputStrings.begin(), inputStrings.end(), [&inputStrings](std::string const& inputStr) {
        client::summand parsed;
        if (parseSummandsInto(inputStr, parsed))
            std::cout << inputStr << " -> (" << parsed.factor << " " << parsed.name << ")\n";
        else
            std::cout << inputStr << " -> FAILED\n";
    });
}

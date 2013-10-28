#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <string>
#include <vector>

enum RectProperty {
    RectPropertyNone                = 0,
    RectPropertyLeft                = 1<<0,
    RectPropertyRight               = 1<<1,
    RectPropertyCentreX             = 1<<2,
    RectPropertyWidth               = 1<<3,
    RectPropertyTop                 = 1<<4,
    RectPropertyBottom              = 1<<5,
    RectPropertyCentreY             = 1<<6,
    RectPropertyHeight              = 1<<7
};

namespace client
{
    namespace spirit = boost::spirit;
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace phoenix = boost::phoenix;

    struct rectProperties_ : qi::symbols<char, unsigned>
    {
        rectProperties_()
        {
            add
                ("cx"   , RectPropertyCentreX)
                ("cy"   , RectPropertyCentreY)
                ("w"    , RectPropertyWidth)
                ("h"    , RectPropertyHeight)
                ("l"    , RectPropertyLeft)
                ("r"    , RectPropertyRight)
                ("t"    , RectPropertyTop)
                ("b"    , RectPropertyBottom)
                ;
        }

    } rectProperties;

    struct summand
    {
        float factor;
        std::string nodeName;
        RectProperty property;
    };

}

BOOST_FUSION_ADAPT_STRUCT(client::summand,
                      (float, factor)
                      (std::string, nodeName)
                      (RectProperty, property)
                      )

namespace client {

template <typename Iterator>
struct summand_parser : qi::grammar<Iterator, std::vector<summand>(), ascii::space_type>
{
    summand_parser() : summand_parser::base_type(start)
    {
        using spirit::float_;
        using ascii::no_case;
        using ascii::alpha;
        using ascii::alnum;

        using qi::lexeme;
        using qi::lit;

        summand_rule %= 
               float_ 
            >> -lit('*') 
            >> '[' 
            >> lexeme[alpha >> *alnum] 
            >> ':' 
            >> no_case[rectProperties] 
            >> ']';

        start = *summand_rule;
    }

    qi::rule<Iterator, summand(), ascii::space_type> summand_rule;
    qi::rule<Iterator, std::vector<summand>(), ascii::space_type> start;
};
}

void parseSummandsInto(std::string const& str, std::vector<client::summand>& summands)
{
    typedef std::string::const_iterator It;
    static const client::summand_parser<It> g;

    It iter = str.begin(), 
       end = str.end();

    bool r = phrase_parse(iter, end, g, boost::spirit::ascii::space, summands);

    if (r && iter == end)
        return;
    else
        throw "Parse failed";
}

int main()
{
    std::vector<client::summand> parsed;
    parseSummandsInto("-5.24 * [HelloWorld : w] -7 * [HelloWorld : b] -8.24 * [HelloWorld : h]", parsed);

    for(auto const& summand : parsed)
        std::cout << "pushed: " << boost::fusion::as_vector(summand) << std::endl;
}

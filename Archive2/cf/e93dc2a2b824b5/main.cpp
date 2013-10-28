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

    std::vector<summand> summands;

    void addToVector(summand const& sum)
    {
        summands.push_back(sum);
    }
}

BOOST_FUSION_ADAPT_STRUCT(client::summand,
                      (float, factor)
                      (std::string, nodeName)
                      (RectProperty, property)
                      )

namespace client {

template <typename Iterator>
struct summand_parser : qi::grammar<Iterator, summand(), ascii::space_type>
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

        start %= summand_rule [phoenix::bind(&addToVector, qi::_1)];
    }

    qi::rule<Iterator, summand(), ascii::space_type> summand_rule;
    qi::rule<Iterator, summand(), ascii::space_type> start;
};
}

float computeSimpleMathExpression(const char * pStr)
{
    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;
    typedef client::summand_parser<iterator_type> summand_parser;

    summand_parser g; // Our grammar
    std::string str("-5.24 * [ HelloWorld : w  ]");

    iterator_type iter = str.begin(), end = str.end();
    bool r = phrase_parse(iter, end, g, space);

    if (r && iter == end)
        return 0;
    else
        throw "Parse failed";
}

int main()
{
    computeSimpleMathExpression(nullptr);
    for(auto const& summand : client::summands)
        std::cout << "pushed: " << boost::fusion::as_vector(summand) << std::endl;
}

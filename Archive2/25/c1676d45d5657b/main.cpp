#define BOOST_SPIRIT_DEBUG
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace qi    = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

struct struct_field
{
    std::string type;
    std::string name;
    int dim;
};

struct struct_body
{
    std::string name;
    std::vector<struct_field> fields;
};

BOOST_FUSION_ADAPT_STRUCT(
    struct_field,
    (std::string, type)
    (std::string, name)
    (int, dim)
)

BOOST_FUSION_ADAPT_STRUCT(
    struct_body,
    (std::string, name)
    (std::vector<struct_field>, fields)
)

template <typename Iterator, typename Skipper>
struct preprocessor :
    qi::grammar<Iterator, struct_body(), Skipper>
{
    preprocessor() :
        preprocessor::base_type(body)
    {
        using namespace qi::labels;
        using qi::eol;
        using qi::graph;
        using qi::lit;
        using qi::lexeme;
        using qi::int_;
        using ascii::char_;

        vartype = +graph;
        varname = +(graph - char_("[;"));
        vardim  = '[' >> int_  >> "]";

        strucname =
            "declare" >> lit('(') >> +~char_(')') >> ')' >>
            eol;

        field =
            vartype >>
            varname >>
            -vardim >>
            ';' >> 
            eol;

        body =
            strucname  >>
            '(' >> eol >>
            *field >>
            ')' >> -eol;

        BOOST_SPIRIT_DEBUG_NODES((body)(field)(strucname)(varname)(vartype)(varname)(vardim))
    }

    qi::rule<Iterator, struct_body(),  Skipper> body;
    qi::rule<Iterator, struct_field(), Skipper> field;
    qi::rule<Iterator, std::string(),  Skipper> strucname;
    qi::rule<Iterator, int(),          Skipper> vardim;
    // lexemes
    qi::rule<Iterator, std::string()> vartype, varname;
};

template<typename Iterator, typename Skipper>
bool parse(Iterator &first, Iterator end, Skipper const &skipper, struct_body &mystruct)
{
    preprocessor<Iterator, Skipper> g;
    return qi::phrase_parse(first, end, g, skipper, mystruct);
}

int main()
{
    std::string const storage = "declare(grid_point)\r\n(\r\n    int    id;\r\n    int    cp;\r\n    double pos[3];\r\n)";
    std::string::const_iterator iter = storage.begin();
    std::string::const_iterator end = storage.end();

    struct_body mystruct;
    bool result = parse(iter, end, qi::blank, mystruct);
    if (result && iter == end)
    {
        std::cout << mystruct.fields.size() << " fields are parsed." << std::endl;
        BOOST_FOREACH(struct_field const& field, mystruct.fields)
        {
            std::cout << field.type << " : " << field.name << " [ " << field.dim << " ] ;" << std::endl;
        }
    }
}

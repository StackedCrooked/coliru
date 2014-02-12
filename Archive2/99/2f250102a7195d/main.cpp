#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <string>
#include <vector>

struct parameter
{
    std::string type;
    std::string name;
};

BOOST_FUSION_ADAPT_STRUCT(
    parameter,
    (std::string, type)
    (std::string, name)
)

inline std::ostream& operator<<(std::ostream& os, const parameter& param) { return os << param.type << ' ' << param.name;  }
inline std::ostream& operator<<(std::ostream& os, const std::vector<parameter>& parameters) {
  for (const auto& param : parameters) { os << param << "; "; }
  return os;
}

struct function
{
    std::vector<parameter> parameters;
};

BOOST_FUSION_ADAPT_STRUCT(
    ::function,
    (std::vector<parameter>, parameters)
)

template <typename Iterator>
struct function_parser : boost::spirit::qi::grammar<Iterator, function(), boost::spirit::qi::ascii::space_type>
{
    function_parser() : function_parser::base_type(start)
    {
        using boost::spirit::qi::alnum;
        using boost::spirit::qi::alpha;

        string %= alpha >> *alnum;
        BOOST_SPIRIT_DEBUG_NODE(string);

        param %= string >> string;
        BOOST_SPIRIT_DEBUG_NODE(param);

        start = boost::spirit::qi::eps >> (param % ',');
        BOOST_SPIRIT_DEBUG_NODE(start);
    }

    boost::spirit::qi::rule<Iterator, std::string()> string;
    boost::spirit::qi::rule<Iterator, parameter(), boost::spirit::qi::ascii::space_type> param;
    boost::spirit::qi::rule<Iterator, function(), boost::spirit::qi::ascii::space_type> start;
};

int main()
{
    std::string input_data("int bar, int baz");

    function fn;
    auto itr = input_data.begin();
    auto end = input_data.end();
    function_parser<decltype(itr)> g;
    bool res = boost::spirit::qi::phrase_parse(itr, end, g, boost::spirit::ascii::space, fn);
    if (res && itr == end)
    {
        std::cout << boost::fusion::tuple_open('[');
        std::cout << boost::fusion::tuple_close(']');
        std::cout << boost::fusion::tuple_delimiter(", ");

        std::cout << "Parsing succeeded \n";
        std::cout << "got: " << boost::fusion::as_vector(fn) << std::endl;
        //std::cout << "got: " << fn << std::endl;
    }
    else
    {
        std::cout << "Parsing failed \n";
    }
}

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

class test
{
    public:
        static test from_string(const std::string &str) { throw "hula"; }
};

template <typename Iterator = std::string::const_iterator>
struct test_parser : qi::grammar<Iterator, test(), qi::blank_type>
{
    test_parser() : test_parser::base_type(query)
    {
        query = id[
                phx::try_ [
                    qi::_val = phx::bind(&test::from_string, qi::_1)
                ].catch_all [ 
                    qi::_pass = false 
                ]
            ];
        id = qi::lexeme[*qi::char_("a-zA-Z_0-9")];
    }
    qi::rule<Iterator, test(), qi::blank_type> query;
    qi::rule<Iterator, std::string(), qi::blank_type> id;
};

int main()
{
    std::string const input = "";
    auto f(begin(input)), l(end(input));

    test_parser<> p;
    test data;
    bool ok = phrase_parse(f,l,p,qi::blank,data);

    return ok? 0 : 255;
}

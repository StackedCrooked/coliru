#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct ExpressionGrammer : qi::grammar<Iterator, double(), ascii::space_type>
{
    qi::rule<Iterator, double(), ascii::space_type> expression;
    qi::rule<Iterator, double(), ascii::space_type> addsub;

    ExpressionGrammer()
    : ExpressionGrammer::base_type(expression)
    {
        using qi::lit;
        using qi::_val;
        using qi::_1;
        using qi::_2;

        addsub = (expression >> '+' >> expression)[_val = _1 + _2];     
        expression = (addsub | qi::double_)[_val = _1];
    }
};

int main()
{
    ExpressionGrammer<char*> g;
}

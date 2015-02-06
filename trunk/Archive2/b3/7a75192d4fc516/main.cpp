#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi_symbols.hpp>
#include <boost/spirit/repository/include/qi_distinct.hpp>
#include <boost/phoenix/stl/cmath.hpp>

namespace qi = boost::spirit::qi;
namespace ascii=boost::spirit::ascii;
using boost::spirit::ascii::space;
using boost::spirit::qi::symbols;


template< typename Iterator >
struct Grammar : public qi::grammar<  Iterator, double(), ascii::space_type >
{

    Grammar() : Grammar::base_type(expression)
    {
        using qi::double_;
        using qi::_val;
        using qi::_1;
        using boost::spirit::repository::qi::distinct;

        expression = double_
                   | distinct(qi::char_("a-zAZ09_")) [ symbol ]
                   | function
                   | group;

        function =  "tan"  >> group [_val = boost::phoenix::tan(_1)];
        group = '(' >> expression >> ')' ;

        BOOST_SPIRIT_DEBUG_NODES((expression)(function)(group));
  }

    qi::rule<Iterator, double(), ascii::space_type> expression, function, group;
    qi::symbols<char, double > symbol;
};


int main()
{
    typedef std::string::iterator iterator;
    Grammar<iterator> grammar;
    std::string function = "tan(t)"; //it would work if function = "tan(x)"
    grammar.symbol.add("t",1.2);     // and add("x",1.2)
    double value;
    bool r = qi::phrase_parse(function.begin(), function.end(), grammar, space, value);
    std::cout << "Exit: " << r << ", value = " << value << std::endl;

    return 0;
}

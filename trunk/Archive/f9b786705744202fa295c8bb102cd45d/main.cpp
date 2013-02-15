#include <boost/fusion/adapted.hpp>
#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi    = boost::spirit::qi;
namespace karma = boost::spirit::karma;
namespace phx   = boost::phoenix;

int main()
{
    typedef std::string::const_iterator It;
    typedef boost::variant<double,int64_t> value_type;
    typedef std::pair<std::string, value_type> dec_type;

    qi::rule<It, value_type(std::string)> value = 
        qi::real_parser<double, qi::strict_real_policies<double>>() /*[ phx::bind(boost::lambda::unlambda(floatDecs.add), qi::_r1, qi::_1) ]*/ |
        qi::int_parser<int64_t, 10>()                               /*[ phx::bind(boost::lambda::unlambda(intDecs.add), qi::_r1, qi::_1)   ]*/;

    qi::rule<It, std::string()> ident = qi::lexeme[ qi::alpha >> *qi::alnum ];

    qi::rule<It, dec_type(), qi::space_type, qi::locals<std::string> > declaration;
    declaration %= ident [qi::_a = qi::_1] >> '=' >> value(qi::_a);

    std::string testing("allo1 = 213.13");
    dec_type parsed;
    bool ok = qi::phrase_parse(testing.cbegin(), testing.cend(), declaration, qi::space, parsed);
    std::cout << "phrase_parse: " << std::boolalpha << ok << "\n";

    using namespace karma;
    std::cout << format(auto_ << " = " << (double_ << 'f' | int_) << eol, parsed);
}

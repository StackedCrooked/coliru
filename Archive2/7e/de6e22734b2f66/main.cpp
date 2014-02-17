#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi_match.hpp>

namespace qi = boost::spirit::qi;
namespace karma = boost::spirit::karma;

int main()
{
    std::vector<std::pair<double, double>> data;

    std::stringstream tmp_stream("{ (132.181,0.683431), (136.886,0.988517), (137.316,0.504297), (133.653,0.602269), (150.86,0.236839) }");

    if (tmp_stream >> std::noskipws >> qi::phrase_match(
                   '{' 
                >> 
                     ( '(' >> qi::double_ >> "," >> qi::double_ >> ')' )
                     % ','
                >> '}',
                qi::space, data))
    {
        std::cout << karma::format(karma::delimit(" ") [karma::auto_] % karma::eol, data) << "\n";
    }
}

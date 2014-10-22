#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_match.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <sstream>
#include <map>

namespace qi = boost::spirit::qi;
typedef qi::real_parser<double, qi::strict_real_policies<double> > sdouble_;
typedef boost::variant<int, double, std::string> value;

int main()
{
    std::istringstream buffer("NbProducts = 1234; SomethingElse = 789.42; Last = 'Some text';");

    std::map<std::string, value> config;

    if (buffer >> std::noskipws >> qi::phrase_match(
            *(+~qi::char_("=") >> '=' >> (qi::lexeme["'" >> *~qi::char_("'") >> "'"] | sdouble_() | qi::int_) >> ';'),
            qi::space, config))
    {
        for(auto& entry : config)
            std::cout << "Key '" << entry.first << "', value: " << entry.second << "\n";
    } else
    {
        std::cout << "Parse error\n";
    }
}

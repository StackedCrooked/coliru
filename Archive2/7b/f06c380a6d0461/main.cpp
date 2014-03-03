#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

int main()
{
    typedef std::string::const_iterator It;
    std::string const input = "cout<<hello;my \"name is\" Hassan";

    qi::rule<It, std::string()> delimiter = qi::char_("; ") | qi::string("<<");
    qi::rule<It, std::string()> quoted    = '"' >> *~qi::char_('"') > '"';
    qi::rule<It, std::string()> word      = +((quoted | qi::char_) - delimiter);

    std::vector<std::string> tokens;
    if (qi::parse(input.begin(), input.end(), *(word >> delimiter), tokens))
    {
        for(auto& token : tokens)
            std::cout << "'" << token <<  "'\n";
    }
}

#include <iostream>
#include <string>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
void use(int x) { std::cout << x << '\n'; }
int main()
{
    std::string str = "12 34 56 78";
    qi::phrase_parse(str.begin(), str.end(), +qi::int_[use], ascii::space);
}

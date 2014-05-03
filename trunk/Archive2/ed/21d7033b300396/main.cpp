#include <iostream>
#include <string>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
int main()
{
    std::string s = "1234";
    int result;
    bool r = qi::phrase_parse(s.begin(), s.end(), qi::int_, ascii::space, result);
    if(r)
        std::cout << result << '\n';
    else
        std::cout << "failed parse\n";
}

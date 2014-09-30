#include <iostream> 
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
namespace qi = boost::spirit::qi;

int main()
{
    for (std::string const input : { 
            "123.456",
            "123",
            ".456" 
            })
    {
        boost::tuple<int, int> output;
        std::string::const_iterator i = input.begin(), l = input.end();
        if (qi::parse(i, l, qi::int_ || ('.' >> qi::int_), output))
        {
            std::cout << "Parsed '" << input << "' ->\t" << boost::get<0>(output) << "\t" << boost::get<1>(output) << "\n";
        } else
        {
            std::cout << "Failed for '" << input << "'\n";
        }

        if (i!=l)
            std::cout << "Remaining input '" << std::string(i,l) << "'\n";
    }

}

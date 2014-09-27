#include <iostream>
#include <utility>
#include <string>

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/std_pair.hpp>

namespace qi=boost::spirit::qi;

int main()
{
    std::string input("123.456");
    std::pair<int,int> output;

    std::string::const_iterator it = input.begin(), end= input.end();
    
    bool result=qi::parse(it, end, qi::int_ || ('.' >> qi::int_), output);
    
    if(result && it==end)
    {
        std::cout << output.first << "_" << output.second << std::endl;
    }
    else
    {
        std::cout << "Something failed. Unparsed: " << std::string(it,end) << std::endl;
    }
}
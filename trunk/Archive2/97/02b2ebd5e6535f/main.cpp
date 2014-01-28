#include <iostream>
#include <string>
#include <utility>
#include <unordered_map>

//#define BOOST_SPIRIT_DEBUG

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/std_pair.hpp>

namespace qi=boost::spirit::qi;



int main()
{
    std::string test="a=b&d=e&f=$$g=h&i=j$$x=y&z=def";
    
    qi::rule<std::string::const_iterator, std::string()> key   =  qi::char_("a-zA-Z_") >> *qi::char_("a-zA-Z_0-9/%\\-_~\\.");
    qi::rule<std::string::const_iterator, std::string()> escapedValue = qi::omit["$$"] >> *(qi::char_ - '$') >> qi::omit["$$"];
    qi::rule<std::string::const_iterator, std::string()> value = *(escapedValue | (qi::char_ - '=' - '&'));
    qi::rule<std::string::const_iterator, std::pair<std::string, std::string>()> pair  =  key >> -('=' >> value);
    qi::rule<std::string::const_iterator, std::unordered_map<std::string, std::string>()> query =  pair >> *(*(qi::lit("&amp;")|'&') >> pair);
    
//    BOOST_SPIRIT_DEBUG_NODES((key)(escapedValue)(value)(pair)(query));
    
    std::string::const_iterator iter=test.begin(), end=test.end();
    std::unordered_map<std::string,std::string> parsed_map;
    
    bool result = qi::parse(iter,end,query,parsed_map);
    
    if(result && iter==end)
    {
        std::cout << "Success. Parsed:" << std::endl;
        for(const auto& pair : parsed_map)
            std::cout << "  (" << pair.first << ", " << pair.second << ")" << std::endl;
    }
    else
    {
        std::cout << "Failure." << std::endl;
    }
}
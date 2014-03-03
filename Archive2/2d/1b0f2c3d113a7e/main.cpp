#include <iostream>
#include <vector>
#include <string>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

namespace qi = boost::spirit::qi;


struct VectorWrapper
{
    std::vector<std::string> data;
};

BOOST_FUSION_ADAPT_STRUCT(
    VectorWrapper,
    (std::vector<std::string>, data)
)

int main ()
{
    std::string input("aa aa aa");
    std::string::iterator strbegin = input.begin();

    qi::rule<std::string::iterator, VectorWrapper(), qi::space_type > testRule = 
        qi::eps >> +(qi::string("aa"));

    VectorWrapper result;
    bool ok = qi::phrase_parse(
            strbegin, 
            input.end(),
            testRule,
            qi::space,                  
            result);                               

    if (ok && strbegin == input.end()) {
        std::cout << result.data.size();
        for (size_t i = 0; i < result.data.size(); ++i) {
            std::cout << result.data[i] << " ";
        }
    } else {
        std::cout << "fail" << std::endl;
        std::cout << std::string(strbegin, input.end()) << std::endl;
    }
}

#include <iostream>
#include <string>
#include <type_traits>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/repository/include/qi_distinct.hpp>

namespace qi=boost::spirit::qi;
namespace qirepo=boost::spirit::repository::qi;



int main()
{
    auto const distinct_word = qirepo::distinct(boost::proto::deep_copy(qi::alnum | '_'));
    
    std::string test="sin_";
    std::string::const_iterator iter=test.begin(),end=test.end();
    
    bool result=qi::parse(iter,end,!distinct_word["sin"]>>*qi::char_);
    
    if(result && iter==end)
    {
        std::cout << "Success." << std::endl;
    }
    else
    {
        std::cout << "Failure." << std::endl;
    }
    
}

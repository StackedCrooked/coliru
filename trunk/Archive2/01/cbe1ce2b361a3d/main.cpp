#include <iostream>

#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/spirit/include/qi_matches.hpp>

#include <string>
#include <vector>
#include <algorithm>

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;


int main(){


    std::vector<std::string> test_inputs = {"14,14,test","14,12,test"};

    std::for_each(test_inputs.begin(),test_inputs.end(),[](const std::string& input){
        boost::fusion::vector<int,int,std::string> result;
        int i(0);
        
        auto res = qi::parse(input.begin(),input.end(),

            qi::int_[phx::ref(i) = qi::_1] >> qi::lit(",") >> qi::int_(phx::ref(i)) >> qi::lit(",") >> +qi::char_,
            result);
        if(res){
            std::cout << "Good: " << result << std::endl;
        }
        else{
            std::cout << "Fail" << std::endl;
        }
    });         
}
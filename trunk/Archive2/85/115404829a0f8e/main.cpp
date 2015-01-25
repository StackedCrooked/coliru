#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

#include <iostream>
#include <vector>
#include <boost/spirit/include/qi_auto.hpp>


namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

using qi::auto_;
using qi::phrase_parse;
using ascii::space;
using phoenix::push_back;

namespace boost { namespace spirit { namespace traits
{
    template <>
    struct create_parser<std::string>
    {
        typedef proto::result_of::deep_copy<
            BOOST_TYPEOF(*(qi::char_-','))
        >::type type;

        static type call()
        {
            return proto::deep_copy(
                *(qi::char_-','));
        }
    };
}}}

template< typename T >
void MyParse(const std::string& line, std::vector<T>& vec)
{
     qi::phrase_parse( line.begin(), 
                       line.end(), 
                       auto_%',', 
                       qi::blank, 
                       vec);
    for(const auto& value : vec)
    {
        std::cout << value << std::endl;
    }
                       
}


int main()
{
    std::string line1 = "1, 2, 3";
    std::string line2 = "apple, orange, banana";

    std::vector<int> vector1;
    std::vector<std::string> vector2;
    
    MyParse(line1,vector1);
    MyParse(line2,vector2);

    

   
    return 0;
}

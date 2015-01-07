#include <iostream>
#include <string>
#include <vector>

#include <boost/fusion/include/boost_tuple.hpp>
#include <boost/spirit/home/qi.hpp>

using namespace boost::spirit::qi;

using entry = boost::tuple<int, float, float>;

template <typename Iterator>
struct sublang : grammar<Iterator, entry(), ascii::space_type>
{
    template<typename Name, typename Body>
    static auto element(Name name, Body body)
    {
        return name >> body;
    }
    
    template<typename AttrName, typename Value>
    static auto attribute(AttrName attrName, Value value)
    {
        return attrName >> ':' >> value;
    }
    
   sublang() : sublang::base_type(start)
   {
       start = int_ >> attribute(float_, float_);
   }
   rule<Iterator, entry(), ascii::space_type> start;
};

int main()
{
    const std::string input = "1 2.0: 3.0";
    sublang<std::string::const_iterator> p;
    
    entry data = { };
    bool result = phrase_parse(std::begin(input), std::end(input), p, ascii::space, data);
    
    std::cout << boost::get<0>(data) << " " << boost::get<1>(data) << " " << boost::get<2>(data);
    
    return result;
}
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
       start = int_ >> float_ >> ':' >> float_;
   }
   rule<Iterator, entry(), ascii::space_type> start;
};

void main()
{
    const std::string input = "1 2.0: 3.0";
    sublang<std::string::const_iterator> p;
    
    entry data;
    bool result = qi::phrase_parse(begin(input), begin(end), p, ascii::space_type, data);
}
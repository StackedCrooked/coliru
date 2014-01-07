#include <iostream>
#include <string>
#include <vector>

//#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;

struct basic_value_t {
  uint8_t type;        
  std::vector<uint8_t> val;
};


BOOST_FUSION_ADAPT_STRUCT
(
 basic_value_t,
 (std::uint8_t, type)
 (std::vector<std::uint8_t>, val)
)

template <typename Iterator_T>
struct my_grammar :
qi::grammar<Iterator_T, std::vector<basic_value_t>() >
{
  my_grammar();

  qi::rule<Iterator_T, std::vector<basic_value_t>() > start;
  qi::rule<Iterator_T, basic_value_t(), qi::locals<size_t> > ptuple;
};

template <typename Iterator_T>
my_grammar<Iterator_T>::
my_grammar() : my_grammar<Iterator_T>::base_type(start), start(), ptuple() {
  start = (*ptuple);

  ptuple
    %= (qi::byte_ >>
       qi::omit[qi::byte_[qi::_a = qi::_1]] >>
       qi::repeat(qi::_a)[qi::byte_])
    ;
}

int main()
{
    std::vector<std::uint8_t> test = {1,3,1,2,3};
    my_grammar<std::vector<std::uint8_t>::const_iterator> grammar;
    
    std::vector<std::uint8_t>::const_iterator iter = test.begin(), end = test.end();
    
    std::vector<basic_value_t> parsed_value_vector;
    
    bool result = qi::parse(iter,end,grammar,parsed_value_vector);
    
    if(result && iter==end)
    {
        std::cout << "Success: Type=" << static_cast<int>(parsed_value_vector[0].type) << "; Vals= ";
        for(int num : parsed_value_vector[0].val)
            std::cout << num << ".";
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Failure." << std::endl;
    }
}
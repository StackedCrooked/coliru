#include <iostream>
#include <string>

#include <boost/spirit/include/karma.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace karma=boost::spirit::karma;

struct data
 {
  std::string str;
 };

BOOST_FUSION_ADAPT_STRUCT(
                      data,
                      (std::string, str)
                      )

template <typename Iterator, typename Delimiter=karma::space_type>
struct data_generator: karma::grammar<Iterator, data(), Delimiter>
{
    data_generator():data_generator::base_type(start)
    {
        start = karma::duplicate[karma::string << karma::lit("some stuff") << karma::string]; //Second string is in fact the first one 
    }
    karma::rule<Iterator, data(), Delimiter> start;
};

int main()
{
    typedef std::back_insert_iterator<std::string> iterator_type;
    std::string generated;
    iterator_type output_it(generated);

    data_generator<iterator_type> g;
    data toto;
    toto.str="toto";
    bool result = karma::generate_delimited(output_it, g, karma::space, toto);
    std::cout << std::boolalpha << result << ":" << generated << std::endl;
}


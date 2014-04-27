#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/fusion/adapted.hpp>
#include <string>
#include <vector>
#include <cmath>

BOOST_PHOENIX_ADAPT_FUNCTION(bool, isnan_, std::isnan, 1)
BOOST_PHOENIX_ADAPT_FUNCTION(bool, isinf_, std::isinf, 1)

template<typename OutputIterator_T>
struct Test_Grammar :
  boost::spirit::karma::grammar<OutputIterator_T, std::vector<double>()>
{
  Test_Grammar() : Test_Grammar::base_type(start), start(), value()
    {
      namespace karma = boost::spirit::karma;
      namespace phx = boost::phoenix;

      start
        = *(value % karma::lit(", "))
        ;

      value
        %= karma::double_ [ karma::_pass = !(isnan_(karma::_1) || isinf_(karma::_1)) ] 
         | karma::lit("special")
         ;
    }

  boost::spirit::karma::rule<OutputIterator_T, std::vector<double>()> start;
  boost::spirit::karma::rule<OutputIterator_T, double()> value;
};

template <typename OutputIterator_T>
bool generate_output(OutputIterator_T& sink, std::vector<double> const& data)
{
    Test_Grammar<OutputIterator_T> grammar;
    return (boost::spirit::karma::generate(sink, grammar, data));
}

int main (int, char**)
{
  std::string generated;
  std::back_insert_iterator<std::string> sink(generated);

  std::vector<double> data{1.5, 0.0, -2.5,
                           std::numeric_limits<float>::quiet_NaN(),
                           std::numeric_limits<float>::infinity()};

  generate_output(sink, data);

  std::cout << generated << std::endl;

  return 0;
}

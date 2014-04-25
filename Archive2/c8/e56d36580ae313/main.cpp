#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/karma.hpp>
#include <boost/fusion/adapted.hpp>
#include <string>
#include <vector>
#include <cmath>

template <typename Num>
struct special_number_policy : boost::spirit::karma::real_policies<Num>
{
        template <typename CharEncoding, typename Tag, typename OutputIterator>
        static bool nan (OutputIterator& sink, Num /*n*/, bool /*force_sign*/)
        {
            return boost::spirit::karma::string_inserter<CharEncoding, Tag>::call(sink, "special");
        }

        template <typename CharEncoding, typename Tag, typename OutputIterator>
        static bool inf (OutputIterator& sink, Num /*n*/, bool /*force_sign*/)
        {
            return boost::spirit::karma::string_inserter<CharEncoding, Tag>::call(sink, "special");
        }
};


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

    }

  boost::spirit::karma::rule<OutputIterator_T, std::vector<double>()> start;
  boost::spirit::karma::real_generator<double,special_number_policy<double> > value;
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

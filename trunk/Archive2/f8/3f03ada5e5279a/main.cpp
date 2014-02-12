#include <boost/fusion/include/define_struct.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

BOOST_FUSION_DEFINE_STRUCT(
  (), foo,
  (int, bar)
  (int, baz)
)

template <typename Iterator, typename Skipper>
    struct parser : qi::grammar<Iterator, foo(), Skipper>
{
    parser() : parser::base_type(start)
    {
        start %= qi::int_ >> qi::int_;
    }

    qi::rule<Iterator, foo(), Skipper> start;
};

int main()
{
  const std::string input_data("0 1");

  foo instance;
  auto itr = input_data.begin();
  auto end = input_data.end();

  qi::rule<decltype(itr)> skipper = 
          qi::ascii::space 
        | ("//" >> *(qi::char_ - qi::eol) >> qi::eol | qi::blank);

  parser<decltype(itr), decltype(skipper)> g;

  bool res = qi::phrase_parse(itr, end, g, skipper, instance);

  if (res && itr == end)
  {
      std::cout << "Parsing succeeded \n";
      std::cout << instance.bar << ' ' << instance.baz << '\n';
  }
  else
  {
      std::cout << "Parsing failed \n";
  }
}

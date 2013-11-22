#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace qi = boost::spirit::qi;

struct container {
  std::string name;
  bool        dummy;
};
BOOST_FUSION_ADAPT_STRUCT(::container,
                          (std::string, name)
                          (bool, dummy))

int main() {
  typedef std::string::const_iterator iterator;

  qi::rule<iterator, std::vector<container>()> all;
  qi::rule<iterator, container()> item;
  qi::rule<iterator, std::string()> string_rule;
  qi::rule<iterator> garbage;

  all         = -(item - garbage) % +garbage;
  garbage     = qi::char_ - qi::lit("Test");
  string_rule = qi::string("Test");
  item        = string_rule >> qi::attr(true);

  std::vector<container> ast;

  std::string input = "blaTestbla";

  iterator first = input.begin();
  iterator last = input.end();

  bool result = qi::parse(first, last, all, ast);
  if (result) {
    result = first == last;
  }

  if (result) {
    std::cout << "Parsed " << ast.size() << " element(s)" << std::endl;
  } else {
    std::cout << "failure" << std::endl;
  }

}

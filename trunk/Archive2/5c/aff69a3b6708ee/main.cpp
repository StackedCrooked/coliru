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
                          
struct container_vector {
    std::vector<container> data;
};

namespace boost{ namespace spirit{ namespace traits
{
    template <>
    struct is_container<container_vector> : boost::mpl::true_ {};
    
    template <>
    struct container_value<container_vector> {
        typedef optional<container> type;
    };
    
    template <>
    struct push_back_container<container_vector,optional<container> > {
        static bool call(container_vector& cont, const optional<container>& val) {
            if(val)
                cont.data.push_back(*val);
            return true;
        }
    };
}}}

int main() {
  typedef std::string::const_iterator iterator;

  qi::rule<iterator, container_vector()> all;
  qi::rule<iterator, container()> item;
  qi::rule<iterator, std::string()> string_rule;
  qi::rule<iterator> garbage;

  all = *(garbage | item);
  garbage = qi::char_ - qi::lit("Test");
  string_rule = qi::string("Test");
  item = string_rule >> qi::attr(true);

  container_vector ast;

  std::string input = "blaTestbla";

  iterator first = input.begin();
  iterator last = input.end();

  bool result = qi::parse(first, last, all, ast);
  if (result) {
    result = first == last;
  }

  if (result) {
    std::cout << "Parsed " << ast.data.size() << " element(s)" << std::endl;
  } else {
    std::cout << "failure" << std::endl;
  }

}
#include <iostream>
#include <boost/spirit/home/qi/action/action.hpp>
#include <boost/spirit/home/qi/string/lit.hpp>

int main() {
  namespace qi = boost::spirit::qi;

  std::string x("ac");
  auto begin = x.begin();
  auto end = x.end();

  const bool ok = qi::parse(begin, end, qi::lit("ab"));
  if (ok) {
    std::cout << "parse ok" << std::endl;
  }
  else {
    std::cout << "parse failed" << std::endl;
    const char* begin_changed = (begin == x.begin()) ? "no" : "yes";
    const char* end_changed = (end == x.end()) ? "no" : "yes";
    
    std::cout << "begin changed? " << begin_changed << std::endl;
    std::cout << "end changed? " << end_changed << std::endl;
  }
}
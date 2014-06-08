#include <iostream>
#include <boost/spirit/include/qi.hpp>

int main() {
  namespace qi = boost::spirit::qi;
  using Iterator = std::string::iterator;

  std::string input = "[[This is some single-spaced text]]";

  qi::rule<Iterator, std::string()> word  = +(qi::char_ - qi::char_(" []"));
  qi::rule<Iterator, std::string()> entry = qi::lit("[[") >> word >> *(qi::char_(' ') >> word) >> qi::lit("]]") >> -qi::eol;

  std::string text;

  Iterator first = input.begin();
  Iterator last = input.end();

  bool r = parse(first, last, entry, text);
  if (r) {
    if (first != last) {
      std::cerr << "not all string parsed" << std::endl;
      return 1;
    }
    std::cout << "parse ok" << std::endl;
    std::cout << "result: " << text << std::endl;
  }
  else {
    std::cerr << "parse failed" << std::endl;
  }
}
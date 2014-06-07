#include <iostream>
#include <boost/spirit/include/qi.hpp>

int main() {
  namespace qi = boost::spirit::qi;
  using Iterator = std::string::iterator;

  std::string x("aabaa");

  try {
    Iterator begin = x.begin();
    Iterator end = x.end();

    const bool ok = qi::parse(begin, end, *qi::char_ > qi::lit('b'));
    if (ok) {
      std::cout << "parse ok" << std::endl;
    }
    else {
      std::cout << "parse failed" << std::endl;
      const char* changed = (begin == x.begin()) ? "no" : "yes";
      std::cout << "begin changed? " << changed << std::endl;
    }
  }
  catch(const qi::expectation_failure<Iterator>& exc) {
    std::cerr << exc.what() << ":" << std::endl;
    std::cerr << x << std::endl;
    std::cerr << std::string(exc.first - x.begin(), ' ') << "^";
    std::cerr << std::endl;
  }
}
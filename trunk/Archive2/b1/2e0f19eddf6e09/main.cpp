#include <cstdio>
#include <string>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

void print(const std::string & str) {
  printf("%s\n", str.c_str());
}

void print_eol() {
  printf("eol\n");
}

int main() {
  std::string str = "a\nb\na -> b\n";
  std::string::iterator it = str.begin(), begin = str.begin(), end = str.end();

  qi::rule<std::string::iterator, std::string()> vertex = +qi::alnum;
  qi::rule<std::string::iterator, std::string()> edge = vertex >> " -> " >> vertex;
  qi::rule<std::string::iterator> start = (edge[&print] | vertex[&print]) % qi::eol[&print_eol] >> qi::eol;

  bool matched = parse(it, end, start);

  if (matched) {
    printf("matched\n");
  }
  if (it == end) {
    printf("all\n");
  } else if (it != begin) {
    printf("some\n");
  } else {
    printf("none\n");
  }

  return 0;
}
#include <iostream>
#include <string>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma_numeric.hpp>
#include <boost/spirit/include/karma_uint.hpp>

namespace bsq = boost::spirit::qi;
namespace bk = boost::spirit::karma;

bsq::int_parser<unsigned char, 16, 2, 2> hex_byte;

template <typename InputIterator>
struct unescaped_string
    : bsq::grammar<InputIterator, std::string(char const *)> {
  unescaped_string() : unescaped_string::base_type(unesc_str) {
    unesc_char.add("+", ' ');

    unesc_str = *(unesc_char | "%" >> hex_byte | bsq::char_);
  }

  bsq::rule<InputIterator, std::string(char const *)> unesc_str;
  bsq::symbols<char const, char const> unesc_char;
};

std::string unescape(const std::string &input) {
  std::string retVal;
  retVal.reserve(input.size());
  typedef std::string::const_iterator iterator_type;

  char const *start = "";
  iterator_type beg = input.begin();
  iterator_type end = input.end();
  unescaped_string<iterator_type> p;

  if (!bsq::parse(beg, end, p(start), retVal))
    retVal = input;
  return retVal;
}

template <typename OutputIterator>
struct escaped_string : bk::grammar<OutputIterator, std::string(char const *)> {
  escaped_string() : escaped_string::base_type(esc_str) {
      esc_str = *(bk::char_("a-zA-Z0-9._~-") | "%" << bk::right_align(2,0)[bk::hex]);
  }
  bk::rule<OutputIterator, std::string(char const *)> esc_str;
};

std::string escape(const std::string &input) {
  typedef std::back_insert_iterator<std::string> sink_type;
  std::string retVal;
  retVal.reserve(input.size() * 3);
  sink_type sink(retVal);
  char const *start = "";

  escaped_string<sink_type> g;
  if (!bk::generate(sink, g(start), input))
    retVal = input;
  return retVal;
}

int main()
{
  std::string testStr;
  testStr.resize(128);
  for (auto i = 0U; i < 128; i++) {
    testStr[i] = static_cast<unsigned char>(i);
  }
  auto escaped = escape(testStr);
  std::cout << "Escaped string: " << escaped << std::endl;
  auto unescaped = unescape(escaped);
  std::cout << "Unescaped string: " << unescaped << std::endl;
  if (testStr == unescaped) {
    std::cout << "Tada!" << std::endl;
  }
  return 0;
}

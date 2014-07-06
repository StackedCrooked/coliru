#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

int main()
{
  namespace qi = boost::spirit::qi;
  typedef std::string::const_iterator Iterator;
  qi::rule<Iterator, qi::locals<char> > test;
  test = qi::char_[qi::_a = qi::_1] >> qi::char_(qi::_a);
  return 0;
}

#include <iostream>
#include <vector>

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/std_pair.hpp>

using namespace std;
using namespace boost;

namespace qi = boost::spirit::qi;

template <typename I> using string_range = iterator_range<I>;

template <typename I> using pair_type = pair<
  boost::optional<int>,
  boost::optional<string_range<I>>
>;

template <typename I> using pairs_type = vector<pair_type<I>>;

using symbol_table = qi::symbols<char, int>;

template <typename Iterator>
struct keys_and_values
  : qi::grammar<Iterator, pairs_type<Iterator>(symbol_table const&)>
{
  keys_and_values()
    : keys_and_values::base_type(query)
  {
    using namespace qi;
    query =  pair (_r1) >> *((qi::lit(';') | '&') >> pair (_r1));
    pair  =  -matches[_r1] >> -('=' >> -value);
    value =  raw[+qi::char_("a-zA-Z_0-9")];
  }
  qi::rule<Iterator, pairs_type<Iterator>(symbol_table const&)> query;
  qi::rule<Iterator, pair_type<Iterator>(symbol_table const&)> pair;
  qi::rule<Iterator, string_range<Iterator>()> value;
};

int main ()
{
  namespace qi = boost::spirit::qi;
  string input { "key1=v1;key2=v2;key3=v3" };

  using string_iterator = string::const_iterator;

  keys_and_values <string_iterator> p;
  pairs_type      <string_iterator> m;

  symbol_table                   keys;
  keys.add ("key1", 1) ("key2", 2) ("key3", 3) ;

  string_iterator begin{boost::begin (input)}, end{boost::end(input)};

  if (qi::parse (begin, end, p(boost::phoenix::ref(keys)), m))
      cout << "parse ok\n";
}
#include <iostream>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>

namespace qi = boost::spirit::qi;

static void print(const std::vector<char>& v) {
   std::cout << std::string(v.begin(), v.end()) << '\n';
}

template<typename Iterator>
struct Grammar : qi::grammar<Iterator, boost::spirit::ascii::space_type> {
    Grammar() : Grammar::base_type(start) 
    {
        start          = string[&print];
        string        %= qi::lexeme['"' >> *unescapedChar >> '"'];
        unescapedChar %= qi::char_ - qi::lit('"');
    }

  private:
    typedef boost::spirit::ascii::space_type space_type;
    qi::rule<Iterator, space_type> start;
    qi::rule<Iterator, std::vector<char>()> string;
    qi::rule<Iterator, char()> unescapedChar;
};

int main() {
   const std::string s("\"how now brown cow\"");
   boost::iostreams::filtering_istream fs(boost::make_iterator_range(s.begin(), s.end()));;

   fs.unsetf(std::ios::skipws);

   typedef boost::spirit::istream_iterator iterator;
   qi::phrase_parse(
      iterator(fs), iterator(),
      Grammar<iterator>(),
      boost::spirit::ascii::space);

   return 0;
}

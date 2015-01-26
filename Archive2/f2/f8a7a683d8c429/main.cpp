#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/at_c.hpp>

namespace qi = boost::spirit::qi;

struct Value;
typedef char String;
typedef std::map<String, Value> Object;
typedef std::vector<Value> Array;
typedef std::pair<Value, String> Get;
typedef std::pair<Value, Value> Plus;
typedef std::pair<std::vector<String>, Value> Template;
struct Value {};

template <typename It, typename Skip>
class grammar : qi::grammar<It, String(), Skip> {
public:
  grammar() : grammar::base_type(string) {
    //string = qi::lexeme['"' >> *(('\\' >> qi::char_('"')) | ~qi::char_('"')) >> '"']
    //    | qi::lexeme['\'' >> *(('\\' >> qi::char_('\'')) | ~qi::char_('\'')) >> '\''];
    string = '\'' >> qi::char_ >> '\'';
    //name = qi::lexeme['@' >> string] | *qi::char_;
    //key = string | name;
    //object = '{' >> -((key >> ':' >> value) % ',' >> -',') >> '}';
    //array = '[' >> -(value % ',' >> -',') >> ']';
    //templ = '<' >> name % ',' >> -',' >> '>' >> value;
    //get = value >> '.' >> key;
    //plus = value >> '+' >> value;
    //value = (string | name | object | array | templ | get | plus)[ [](auto const& i){}];
  }
private:
  qi::rule<It, Value(), Skip> value;
  qi::rule<It, String(), Skip> string, name, key;
  qi::rule<It, Object(), Skip> object;
  qi::rule<It, Array(), Skip> array;
  qi::rule<It, Get(), Skip> get;
  qi::rule<It, Plus(), Skip> plus;
  qi::rule<It, Template(), Skip> templ;
};

template <typename It>
bool parse(It const& it, It const& l, String& value) {
  static const grammar<It, qi::space_type> p;
  return qi::phrase_parse(it, l, p, qi::space, value);
}

int main() {
  std::string input("'YAY'");
  std::string result;
  qi::parse(input.begin(), input.end(), '\'' >> *qi::char_ >> '\'', result);
  std::cout << result << std::endl;
  return 0;
}
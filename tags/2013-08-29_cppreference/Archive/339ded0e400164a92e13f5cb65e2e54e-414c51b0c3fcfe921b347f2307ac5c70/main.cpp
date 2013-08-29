#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

//------------------------------------------------------------------------------
// Data structure
struct myline {
  myline()
      : _n(0), _s("") {
  }

  myline(int n, std::string s)
      : _n(n), _s(s) {
  }

  void set(int n, std::string s) {
    _n = n;
    _s = s;
  }

  int _n;
  std::string _s;
};

BOOST_FUSION_ADAPT_STRUCT(::myline, (int, _n) (std::string, _s))

//------------------------------------------------------------------------------
// Parser grammar
template<typename It, typename Skipper = qi::space_type>
struct parser: qi::grammar<It, myline(), Skipper> {
  parser()
      : parser::base_type(start) {
    using namespace qi;

    start  = line;

    string = qi::lexeme["'" >> *~qi::char_("'") >> "'"];

    one    = (string >> "@" >> qi::int_) [_val           = phx::construct<myline>(_2, _1)];
    two    = (qi::int_ >> "@" >> string);

    keyword.add("one", &one)("two", &two);

    // NOTE the %=
    line %= omit [ keyword[_a = _1] ] >> qi::lazy(*_a);

    on_error<fail>(
        start,
        std::cout << phx::val("Error! Expecting ") << _4
        << phx::val(" here: \"") << phx::construct<std::string>(_3, _2)
        << phx::val("\"\n"));

    BOOST_SPIRIT_DEBUG_NODES((start)(line)(one)(two))
  }

private:
  template<typename Attr> using Rule = qi::rule<It, Attr(), Skipper>;

  Rule<myline> start, one, two;
  qi::rule<It, myline(), Skipper, qi::locals<Rule<myline>*> > line;

  Rule<std::string> string;

  qi::symbols<char, Rule<myline>* > keyword;
};

//------------------------------------------------------------------------------
int main() {
  for (const std::string input : std::vector<std::string> { "one 'test1'@1",
                                                            "two 2@'test2'" }) {
    auto f(std::begin(input)), l(std::end(input));
    const static parser<decltype(f)> p;

    myline parsed_script;
    bool ok = qi::phrase_parse(f, l, p, qi::space, parsed_script);

    if (!ok) {
      std::cout << "invalid input\n";
    }

    std::cout << parsed_script._n << ": " << parsed_script._s << std::endl;

    if (f != l) {
      std::cout << "unparsed: '" << std::string(f, l) << "'" << std::endl;
    }
  }
}

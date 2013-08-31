#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <string>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

typedef qi::symbols<char, int> Symbols;

struct assign_symbol_f
{
    assign_symbol_f(Symbols& sym) : sym(sym) {}

    typedef bool result_type;

    template<typename Key, typename Value>
    bool operator()(Key const& key, Value const& value) const
    {
        bool replaced = (nullptr != sym.find(key));

        sym.remove(key); 
        sym.add(key, value);
        
        return replaced;
    }

private:
    Symbols& sym;
};

template <typename Iter> struct parser : qi::grammar<Iter, qi::space_type> 
{
    parser(Symbols &dict) 
        : parser::base_type(start), 
          assign_sym(dict)
    {
        using namespace qi;
        identifier = +graph;

        add_rule = lit("+") >> (identifier >> int_)
            [ assign_sym(_1, _2) ]
            ;

        del_rule = lit("-") >> identifier
            [ phx::bind(dict.remove, _1) ]
            ;

        start = (del_rule | add_rule) % ";";
    }

  private:
    phx::function<assign_symbol_f> assign_sym;

    qi::rule<Iter, qi::space_type> start, del_rule, add_rule;
    qi::rule<Iter, std::string()> identifier; // no skipper
};

bool execute(std::string const& test, Symbols& dict)
{
    auto f = test.begin(), l = test.end();

    parser<std::string::const_iterator> prsr(dict);
    return 
        qi::phrase_parse(f, l, prsr, qi::space)
        && (f == l);
}

int main() {
    Symbols dict;

    assert(execute("+foo 3; +bar 4; -foo", dict));
    
    assert(!dict.find("foo"));
    assert( dict.find("bar") && (4 == dict.at("bar")));
    assert(!dict.find("zap"));

    assert(execute("+zap -42; +bar 5; +foo 33", dict));

    assert( dict.find("zap") && (-42 == dict.at("zap")));
    assert( dict.find("bar") && (5   == dict.at("bar"))); // replaced
    assert( dict.find("foo") && (33  == dict.at("foo")));
}

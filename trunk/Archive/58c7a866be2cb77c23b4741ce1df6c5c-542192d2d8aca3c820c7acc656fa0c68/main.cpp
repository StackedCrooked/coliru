 #define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

template <typename It, typename Skipper>
struct NewGrammar; // forward declare for friend declaration

template <typename It, typename Skipper>
struct OldGrammar : qi::grammar<It, Skipper, std::string()>
{
    friend struct NewGrammar<It, Skipper>; // NOTE

    OldGrammar() : OldGrammar::base_type(mainrule)
    {
        using namespace qi;
        rule1 = int_(1); // expect version 1
        rule2 = *char_;  // hopefully some interesting grammar
        mainrule = omit [ "version" > rule1 ] >> rule2;

        BOOST_SPIRIT_DEBUG_NODE(mainrule);
        BOOST_SPIRIT_DEBUG_NODE(rule1);
        BOOST_SPIRIT_DEBUG_NODE(rule2);
    }
  private:
    qi::rule<It, Skipper, std::string()> mainrule;
    qi::rule<It, Skipper, int()>         rule1;
    qi::rule<It, Skipper, std::string()> rule2;
};

template <typename It, typename Skipper>
struct NewGrammar : qi::grammar<It, Skipper, std::string()>
{
    NewGrammar() : NewGrammar::base_type(mainrule)
    {
        using namespace qi;
        new_rule1 = int_(2); // expect version 2 now
        new_start = omit [ "version" >> new_rule1 ] >> old.rule2; // note, no expectation point

        mainrule = new_start 
                 | old.mainrule;  // or fall back to version 1 grammar

        BOOST_SPIRIT_DEBUG_NODE(new_start);
        BOOST_SPIRIT_DEBUG_NODE(mainrule);
        BOOST_SPIRIT_DEBUG_NODE(new_rule1);
    }
  private:
    OldGrammar<It, Skipper> old;
    qi::rule<It, Skipper, std::string()> new_start, mainrule;
    qi::rule<It, Skipper, int()>         new_rule1;
};

template <template <typename It,typename Skipper> class Grammar>
bool test(std::string const& input)
{
    auto f(input.begin()), l(input.end());
    static const Grammar<std::string::const_iterator, qi::space_type> p;
    try {
        return qi::phrase_parse(f,l,p,qi::space) && (f == l); // require full input consumed
    } 
    catch(...) { return false; } // qi::expectation_failure<>
}

int main()
{
    assert(true  == test<OldGrammar>("version 1 woot"));
    assert(false == test<OldGrammar>("version 2 nope"));

    assert(true  == test<NewGrammar>("version 1 woot"));
    assert(true  == test<NewGrammar>("version 2 woot as well"));
}


#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

template <typename It>
struct DiamidentGrammar : public qi::grammar<It>
{
    DiamidentGrammar() : DiamidentGrammar::base_type(diameterIdentity)
    {
        using namespace qi;
        diameterDname    = digit >> +(alnum | '-');
        diameterName     = alpha >> *(alnum | '-');
        label            = diameterName | diameterDname;
        realm            = label % '.'; 
        diameterIdentity = realm;
    };
  private:
    qi::rule<It> diameterIdentity, realm, label, diameterName, diameterDname;
};

int main()
{
    DiamidentGrammar<std::string::const_iterator> p;
}

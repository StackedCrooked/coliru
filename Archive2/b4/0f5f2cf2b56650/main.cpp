#include <boost/spirit/include/qi.hpp>
namespace qi = boost::spirit::qi;

template <typename It>
struct DiamidentGrammar : public qi::grammar<It>
{
    DiamidentGrammar() : DiamidentGrammar::base_type(diameterIdentity)
    {
        using namespace qi;
        diameterIdentity = realm;
        realm            = label % '.'; 
        label            = diameterName | diameterDname;
        diameterName     = alpha >> *(alnum | '-');
        diameterDname    = digit >> +(alnum | '-');
    };
  private:
    qi::rule<It> diameterIdentity, realm, label, diameterName, diameterDname;
};

int main()
{
    DiamidentGrammar<std::string::const_iterator> p;
}

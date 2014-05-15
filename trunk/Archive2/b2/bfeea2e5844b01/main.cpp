#include <boost/spirit/include/classic.hpp>

using namespace boost::spirit::classic;

struct DiamidentGrammar : public grammar<DiamidentGrammar>
{
    template <typename ScannerT>
        struct definition
        {
            definition(DiamidentGrammar const& self)  
            { 
                diameterIdentity = realm;
                realm = label >> *('.' >> label);  // No recursive rule allowed.
                label = diameterName | diameterDname;
                diameterName = alpha_p >> *(alnum_p | '-');
                diameterDname = digit_p >> +(alnum_p | '-');
            }
            rule<ScannerT> diameterIdentity, realm, label, diameterName, diameterDname;
            rule<ScannerT> const& start() const { return diameterIdentity; }
        };
};

int main()
{
}

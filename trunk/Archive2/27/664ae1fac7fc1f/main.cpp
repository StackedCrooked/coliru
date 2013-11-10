#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

int main()
{
    for (std::string s : { "bla" , "blo" })
    {
        auto f(begin(s)), l(end(s));

        bool ok = qi::parse(f,l,+qi::char_);
        assert(ok);
    }
}

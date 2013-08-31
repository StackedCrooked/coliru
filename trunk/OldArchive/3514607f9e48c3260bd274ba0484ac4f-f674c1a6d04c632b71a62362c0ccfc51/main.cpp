#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi    = boost::spirit::qi;
namespace karma = boost::spirit::karma;
namespace phx   = boost::phoenix;

int main()
{
    using namespace std;
    const string x = "1,2,3;2,3,4;3,4,5";
    auto f(begin(x)), l(end(x));

    vector<vector<short>> data;

    if (qi::parse(f, l, 
            (qi::eps(phx::size(qi::_val) < 2) > (qi::short_ % ',')) % ';'
            , data))
    {
        cout << karma::format(karma::short_ % ',' % ';', data) << "\n";
    }
    cout << "remaining unparsed: '" << std::string(f,l) << "'\n";
}

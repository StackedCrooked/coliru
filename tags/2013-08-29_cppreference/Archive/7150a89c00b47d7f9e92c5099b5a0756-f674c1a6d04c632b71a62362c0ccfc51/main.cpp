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

    qi::rule<string::const_iterator, vector<short>()> sub;
    qi::rule<string::const_iterator, vector<vector<short>>()> rule;

    sub   = qi::short_ % ',';
    rule %= (qi::eps(phx::size(qi::_val) < 2) > sub) % ';';

    if (qi::parse(f, l, rule, data))
    {
        cout << karma::format(karma::short_ % ',' % ';', data) << "\n";
    }
    cout << "remaining unparsed: '" << std::string(f,l) << "'\n";
}

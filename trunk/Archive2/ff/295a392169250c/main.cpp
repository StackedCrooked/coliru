#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

int main() { 
    using namespace qi;

    std::string const s("{A,B,C:D,E}");

    std::vector<char> parsed;

    bool ok = qi::parse(begin(s), end(s),
            '{' >> 
                (
                      "C:" >> qi::char_("A-Z") [ qi::_1 = 'Z' - (qi::_1 - 'A') ]
                    | qi::char_("A-Z")
                ) % ','
            >> '}', 
            parsed);

    if (ok) {
        std::copy(begin(parsed), end(parsed), std::ostream_iterator<char>(std::cout, "; "));
    }
}

#include <boost/spirit/include/qi.hpp>
#include <cstring>

namespace qi = boost::spirit::qi;

int main() {
    for (auto&& s : { "bla" , "blo" }) {
        auto begin(a);
        auto end(a + std::strlen(s));
        bool ok = qi::parse(begin, end, +qi::char_);
        assert(ok);
    }
    
    return 0;
}

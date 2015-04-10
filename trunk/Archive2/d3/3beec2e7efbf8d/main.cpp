#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
using namespace qi::labels;
using qi::eps;

template <typename Iterator, typename Any>
struct parser : qi::grammar<Iterator, Any(), qi::locals<bool> > {
    parser() : parser::base_type(p) {
        p = eps[_a=false] >> eps(_a);
    }
    qi::rule<Iterator, Any(), qi::locals<bool> > p;
};

int main(int argc, const char *argv[]) {
    int val;
    std::string data;
    auto i = data.cbegin();
    auto end = data.cend();
    parser<decltype(i), decltype(val) > p;
    bool rv = phrase_parse(i, end, p, ascii::blank, val);
    return rv ? 0 : 1;
}
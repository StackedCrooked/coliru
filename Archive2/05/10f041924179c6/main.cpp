#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <string>
#include <iostream>

namespace qi = boost::spirit::qi;
using std::string;
using std::cout;
using std::endl;

void
test_input(const string &input)
{
    string::const_iterator b = input.begin();
    string::const_iterator e = input.end();
    string parsed;
    bool const r = qi::phrase_parse(b, e,
        qi::raw [ *(qi::char_ - qi::char_("(")) ] >> qi::lit("(Spirit)"),
        qi::space,
        parsed
    );
    if(r) {
        cout << "PASSED:" << endl;
    } else {
        cout << "FAILED:" << endl;
    }
    cout << "  Parsed: \"" << parsed << "\"" << endl;
    cout << "  Rest: \"" << string(b, e) << "\"" << endl;
}

int main()
{
    test_input("Fine (Spirit)");
    test_input("Hello, World (Spirit)");

    return 0;
}

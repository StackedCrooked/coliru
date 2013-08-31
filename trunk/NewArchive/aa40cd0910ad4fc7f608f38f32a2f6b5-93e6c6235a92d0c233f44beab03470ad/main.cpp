#include <boost/spirit/include/qi.hpp>
#include <cassert>

namespace qi = boost::spirit::qi;

template<typename ParseExpr, typename... Attr>
void test(const std::string& input, const ParseExpr& p, Attr&... attrs)
{
    auto f = input.begin(), 
         l = input.end();

    bool ok = qi::phrase_parse(f,l, p, qi::space, attrs...);

    if (!ok)
        std::cerr << "parse failed at: '" << std::string(f,l) << "'\n";

    if (f!=l) 
        std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";
}

int main()
{
    char parsed_char1, parsed_char2;
    int parsed_int;
    std::string parsed_str;

    test("( 0 )",                        // input
         '(' >> qi::char_("0-9") >> ')', // parser/grammar
         parsed_char1                     // output
    );
    assert(parsed_char1 == '0');

    test("( q 123 )", 
            '(' >> qi::graph >> qi::int_ >> ')', 
            parsed_char1, 
            parsed_int);
    assert(parsed_char1 == 'q');
    assert(parsed_int == 123);

    // parsing strings: with the skipper
    test("( hello world )", 
        '(' >> *~qi::char_(")") >> ')', 
        parsed_str = "");
    assert(parsed_str == "helloworld");

    // parsing strings: qi::char_ exposes the char
    test("( hello world )", 
        qi::char_('(') >>  *~qi::char_(")") >> qi::char_(')'), 
        parsed_char1, parsed_str = "", parsed_char2);
    assert(parsed_char1 == '(');
    assert(parsed_str == "helloworld");
    assert(parsed_char2 == ')');

    // parsing strings: qi::char_ exposes the char, chars get 'combined' into attribute
    test("( hello world )", 
        qi::char_('(') >>  *~qi::char_(")") >> qi::char_(')'), 
        parsed_str = "");
    assert(parsed_str == "(helloworld)");

    // parsing strings: as a lexeme
    test("( hello world )", 
        '(' >> qi::lexeme [ *~qi::char_(")") ] >> ')', 
        parsed_str = "");
    assert(parsed_str == "hello world ");

    // parsing strings: as bigger lexeme
    test("( hello world )", 
        qi::lexeme [ '(' >>  *~qi::char_(")") >> ')' ], 
        parsed_str = "");
    assert(parsed_str == " hello world ");

    // parsing anything as "raw" - exposes an iterator pair, but still 'converts' to a string!
    test("( hello 42 false )", 
        qi::raw [ '(' >>  qi::lexeme[*qi::graph] >> qi::int_ >> qi::bool_ >> ')' ], 
        parsed_str = "");
    assert(parsed_str == "( hello 42 false )");

    // note: this would fail to parse, because with the skipper, *qi::graph would eat "42 false )" as well:
    std::cout << "next parse should fail:\n";
    test("( hello 42 false )", qi::raw [ '(' >>  *qi::graph >> qi::int_ >> qi::bool_ >> ')' ]);
}

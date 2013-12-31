#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/repository/include/qi_distinct.hpp>
#include <fstream>

namespace qi = boost::spirit::qi;
namespace phx= boost::phoenix;

using It      = std::string::const_iterator;
using Skipper = qi::space_type;
using Rule    = qi::rule<It, Skipper>;

template <typename G, size_t N>
    bool test(const char (&raw)[N], const G& grammar)
{
    std::string const input(raw, raw+N-1);
    auto f(std::begin(input)), l(std::end(input));
    try
    {
        bool ok = qi::phrase_parse(f, l, grammar, qi::space);
        if (f!=l)
            std::cerr << "remaining unparsed: '" << std::string(f,l) << "'\n";
        return ok && (f == l); 
    } catch (qi::expectation_failure<It> const& e)
    {
        std::cout << "Expectation failure '" << e.what() << "' at '" << std::string(e.first, e.last) << "'\n";
        return false;
    }
}

template <typename It, typename Skipper>
struct toy_grammar : qi::grammar<It, Skipper>
{
    toy_grammar() : toy_grammar::base_type(start)
    {
        using boost::spirit::repository::distinct;
        static const auto kw = distinct(qi::char_("a-zA-Z_0-9"));

        keywords.add("let")("declare")("begin")("end")("for")("call")("if")("else");

        identifier = !kw[keywords] >> qi::lexeme [ qi::alpha >> *qi::char_("a-zA-Z_0-9") ];
        
        assert( test("z", identifier));
        assert( test("Afgjkj_123123", identifier));
        assert(!test("1", identifier));

        type       = qi::lexeme [ kw["int"] | kw["double"]| kw["string"] | kw["boolean"]];

        assert( test("int",     type));
        assert( test("double",  type));
        assert( test("string",  type));
        assert( test("boolean", type));
        assert(!test("intzies", type));
        assert(!test("Int",     type));

        literal    = qi::lexeme [
                    qi::real_parser<double, qi::strict_real_policies<double>>()
                    | qi::int_
                    | qi::as_string ['"' >> *~qi::char_('"') >> '"']
                    | kw [ qi::bool_ ]
                    ];

        assert( test("42",     literal));
        assert( test("42.",    literal));
        assert( test(".0",     literal));
        assert( test("-3e+7",  literal));
        assert( test("-inf",   literal));
        assert( test("-99",    literal));
        assert( test("\"\"",   literal));
        assert( test("\"\0\"", literal));
        assert( test("true",   literal));
        assert( test("false",  literal));
        assert(!test("trueish",literal));
        assert(!test("yes",    literal));

        invocation = identifier > '(' > -(expression % ',') > ')';

        // arhem, this part left as an exercise for the reader :)
        expression = literal | identifier | (kw["call"] > invocation); 

        assert( test("-99",       expression));
        assert( test("\"santa\"", expression));
        assert( test("clause",    expression));
        assert( test("true",      expression));
        assert( test("call foo()",    expression));
        assert( test("call foo(bar, inf, false)", expression));
        assert(!test("call 42()",     expression));

        // let's have some language constructs
        feature_vardecl    = identifier >> ':' >> type >> ';';
        feature_assignment = identifier >> "=" >> expression >> ';';
        feature_block      = *statement >> kw["end"] >> ';' | statement;
        feature_forloop    = '(' >> identifier >> ':' >> identifier > ')' >> statement;
        feature_func_call  = invocation > ';';
        feature_if_else    = ('(' > expression > ')' > statement) >> (kw["else"] > statement);

        language_constructs.add
            ("declare", &feature_vardecl)
            ("let",     &feature_assignment)
            ("begin",   &feature_block)
            ("if",      &feature_if_else)
            ("for",     &feature_forloop)
            ("call",    &feature_func_call);

        statement  = 
              (kw[language_constructs] [ qi::_a = qi::_1 ] > qi::lazy(*qi::_a))
            | (expression > ';');

        assert( test("declare x : int;"                                       , statement));
        assert( test("let y = true;"                                          , statement));
        assert( test("call foo();",                                             statement));
        assert( test("call foo(bar, inf, false);",                              statement));

        assert( test("begin end;",                                              statement));
        assert( test("begin let y = x; end;",                                   statement));
        assert( test("begin let y = x; call foo(y); end;",                      statement));
        assert( test("for (x : collection) begin let y = x; call foo(y); end;", statement));

        BOOST_SPIRIT_DEBUG_NODES((identifier)(type)(literal)(expression)(invocation)(statement)
                (feature_vardecl)(feature_assignment)(feature_block)(feature_forloop)(feature_func_call)(feature_if_else)
                );

        start = statement;
    }
  private:
    qi::symbols<char, Rule const*> language_constructs;
    qi::symbols<char, qi::unused_type> keywords;

    Rule start,
         identifier, type, literal, expression, invocation, 
         feature_assignment, feature_vardecl, feature_block, feature_forloop, feature_func_call, feature_if_else;

    qi::rule<It, Skipper, qi::locals<Rule const*> > statement;
};

int main()
{
    using namespace std;
    ifstream ifs("input.txt", ios::binary);
    string const input(istreambuf_iterator<char>(ifs), {});

    auto f(begin(input)), l(end(input));
    try
    {
        static const toy_grammar<It, Skipper> p;
        bool ok = qi::phrase_parse(
                f, l,
                p,
                qi::space);

        assert(ok);

        if (f!=l)
            cout << "Program remaining unparsed: '" << string(f,l) << "'\n";
    } catch (qi::expectation_failure<It> const& e)
    {
        cout << "Expectation failure '" << e.what() << "' at '" << string(e.first, e.last) << "'\n";
    }
}

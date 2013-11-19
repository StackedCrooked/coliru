#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
// #include <boost/spirit/include/phoenix.hpp>
#include <deque>

namespace qi    = boost::spirit::qi;
namespace karma = boost::spirit::karma;
typedef std::string::const_iterator It;

namespace ast
{
    using expression = boost::variant<int, std::string>;

    struct vardecl
    {
        std::string name;
        boost::optional<expression> initializer;
    };
}

BOOST_FUSION_ADAPT_STRUCT(ast::vardecl, (std::string, name)(boost::optional<ast::expression>, initializer))

template <typename Result, typename Parser, typename Generator = karma::auto_type>
bool test(std::string const& input, Parser const& p, Generator const& g = karma::auto_)
{
    std::cout << "--------------------------------------------------\n";
    std::cout << "parsing '" << input << "':\n";
    std::cout << "--------------------------------------------------\n";
    It f(begin(input)), l(end(input));

    Result parsed;

    bool ok = qi::phrase_parse(f, l, p, qi::space, parsed);
    if (ok)   
    {
        std::cout << "parse success\n";
        std::cout << "data: " << karma::format_delimited(g, "\n\t", parsed) << "\n";
    }
    else std::cerr << "parse failed: '" << std::string(f,l) << "'\n";

    if (f!=l) std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";

    return ok;
}

int main()
{
    assert(test<ast::expression>("1", qi::int_));
    assert(test<ast::expression>("'string'", qi::as_string [ qi::lexeme [ "'" >> *~qi::char_("'") >> "'" ] ]));

    const static qi::rule<It, ast::expression(), qi::space_type> expression = 
              qi::int_ 
            | qi::lexeme [ "'" >> *~qi::char_("'") >> "'" ];

    using expressions = std::set<ast::expression>;
    assert(test<expressions>("'string'; 1; ' more text '\n"
                             ";'';-42", expression % ';'));

    const static qi::rule<It, std::string(),  qi::space_type> identifier = qi::lexeme [ (qi::alpha|'_') >> *(qi::alnum|'_') ];
    const static qi::rule<It, ast::vardecl(), qi::space_type> vardecl    = 
              identifier > -('=' > expression);

    using statement  = boost::variant<ast::expression, ast::vardecl>;
    using block      = std::deque<statement>;
    assert(test<block>("\n"
        "{\n"
        "    'string'; \n"
        "    my_variable = 1; \n"
        "    ' more text '\n"
        "    ;''; _r1 = -42\n"
        "}", 
        // parser:
        '{' >> (vardecl | expression) % ';' >> '}',
        // generator:
        '{' << (karma::stream | karma::auto_) % ';' << '}'
    ));
#if 0
#endif
}

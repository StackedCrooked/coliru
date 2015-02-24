//#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>

namespace qi    = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

namespace ast {

    namespace tag {
        struct constant;
        struct variable;
        struct function;
    }

    template <typename Tag> struct Identifier { char name; };

    using Constant = Identifier<tag::constant>;
    using Variable = Identifier<tag::variable>;
    using Function = Identifier<tag::function>;

    struct FunctionCall;

    using Expression = boost::make_recursive_variant<
        Constant,
        Variable,
        boost::recursive_wrapper<FunctionCall>
    >::type;

    struct FunctionCall {
        Function function;
        std::vector<Expression> params;
    };

    struct Equation {
        Expression lhs, rhs;
    };
}

BOOST_FUSION_ADAPT_STRUCT(ast::Constant, (char, name))
BOOST_FUSION_ADAPT_STRUCT(ast::Variable, (char, name))
BOOST_FUSION_ADAPT_STRUCT(ast::Function, (char, name))
BOOST_FUSION_ADAPT_STRUCT(ast::FunctionCall, (ast::Function, function)(std::vector<ast::Expression>, params))
BOOST_FUSION_ADAPT_STRUCT(ast::Equation, (ast::Expression, lhs)(ast::Expression, rhs))

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename It, typename Skipper = ascii::space_type>
struct Parser : qi::grammar<It, ast::Equation(), Skipper>
{
    Parser() : Parser::base_type(equation_)
    {
        using namespace qi;

        constant_ = qi::eps >> char_("a-eA-E");
        function_ = qi::eps >> char_("f-rF-R");
        variable_ = qi::eps >> char_("s-zS-Z");

        function_call = function_ >> '(' >> -(expression_ % ',') >> ')';
        expression_   = constant_ | variable_ | function_call;
        equation_     = expression_ >> '=' >> expression_;

        BOOST_SPIRIT_DEBUG_NODES((constant_)(function_)(variable_)(function_call)(expression_)(equation_))
    }
    qi::rule<It, ast::Constant()> constant_;
    qi::rule<It, ast::Function()> function_;
    qi::rule<It, ast::Variable()> variable_;

    qi::rule<It, ast::FunctionCall(), Skipper> function_call;
    qi::rule<It, ast::Expression(),   Skipper> expression_;
    qi::rule<It, ast::Equation(),     Skipper> equation_;
};

int main() {
    std::cout << "Unification Algorithm\n\n";

    std::string const phrase = "f(a, b) = f(g(z, x), g(x, h(x)), c)";
    using It = std::string::const_iterator;
    It itr = phrase.begin(), last = phrase.end();

    std::cout << phrase << std::endl;

    // Parser grammar
    Parser<std::string::const_iterator> g;

    // Output data
    ast::Equation parsed;

    if (phrase_parse(itr, last, g, ascii::space, parsed)) {
        std::cout << "Expression parsed.\n";
    } else {
        std::cout << "Could not parse equation.\n";
    }

    if (itr != last) {
        std::cout << "Remaining unparsed input: '" << std::string(itr,last) << "'\n";
    }
}

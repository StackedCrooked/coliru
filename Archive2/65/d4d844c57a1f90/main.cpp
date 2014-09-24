//#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/range/numeric.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <fstream>
#include <map>

namespace ast {
    using namespace boost;

    using Value = double; // int, if you prefer
    using Id    = boost::optional<int>;

    struct addition;
    struct subtraction;
    struct multiplication;
    struct division;

    using expression = variant<
            Value,
            recursive_wrapper<addition>, 
            recursive_wrapper<subtraction>,
            recursive_wrapper<multiplication>,
            recursive_wrapper<division>
        >;

    using expressions = std::vector<expression>;

    struct has_result_id {
        Id id = none;
    };

    struct literal : has_result_id {
        expressions items;
    };

    struct addition : has_result_id {
        expressions items;
    };

    struct subtraction : has_result_id {
        expression minuend, subtrahend;
    };

    struct multiplication : has_result_id {
        expressions factors;
    };

    struct division : has_result_id {
        expression dividend, divisor;
    };

    struct get_id_ : static_visitor<Id> {
        Id operator()(has_result_id const& e) const { return e.id; }
        Id operator()(Value const& v)         const { return none; }
    };
}

BOOST_FUSION_ADAPT_STRUCT(ast::addition,       (ast::Id, id) (ast::expressions, items   ))
BOOST_FUSION_ADAPT_STRUCT(ast::subtraction,    (ast::Id, id) (ast::expression,  minuend ) (ast::expression, subtrahend))
BOOST_FUSION_ADAPT_STRUCT(ast::multiplication, (ast::Id, id) (ast::expressions, factors))
BOOST_FUSION_ADAPT_STRUCT(ast::division,       (ast::Id, id) (ast::expression,  dividend) (ast::expression, divisor))

namespace /*parser*/
{
    namespace qi = boost::spirit::qi;

    template <typename It, typename Skipper = qi::space_type>
        struct grammar : qi::grammar<It, ast::expressions(), Skipper>
    {
        grammar() : grammar::base_type(expressions_)
        {
            using namespace qi;

            static const lexeme_type L;

            simplevalue_ = auto_; // parses into Value, whatever it was declared as
            id_attr      = eps >> L["id"]      > '=' > '"' > int_        > '"';
            complex_attr = eps >> L["complex"] > '=' > '"' > *~char_('"') > '"';
            expr_open    = eps >> '<' >> L[lit(_r1)] > -id_attr > -complex_attr > '>';
            expr_close   = eps >> '<' >> '/' > L[lit(_r1)] > '>';

            // expression element parsing
            addition_       = expr_open(+"addition") > +subexpr_(+"item")                                  > expr_close(+"addition");
            subtraction_    = expr_open(+"subtraction") > (subexpr_(+"minuend") > subexpr_(+"subtrahend")) > expr_close(+"subtraction");
            multiplication_ = expr_open(+"multiplication") > +subexpr_(+"factor")                          > expr_close(+"multiplication");
            division_       = expr_open(+"division") > (subexpr_(+"dividend") > subexpr_(+"divisor"))      > expr_close(+"division");
            expression_     = simplevalue_ | addition_ | subtraction_ | multiplication_ | division_;

            subexpr_ = eps >> '<' >> L[lit(_r1)] > '>' > expression_ > '<' > '/' > L[lit(_r1)] > '>';

            expressions_ = eps
                > '<' > L["expressions"] > '>'
                > *expression_
                > expr_close(+"expressions");

            BOOST_SPIRIT_DEBUG_NODES((simplevalue_)(expr_open)(expr_close)(subexpr_)(addition_)(subtraction_)(multiplication_)(division_)(expression_)(expressions_))
        }
      private:
        template <typename... T>
            using Rule = qi::rule<It, T..., qi::space_type>;

        // tags/primitives
        Rule<> complex_attr;
        Rule<int()> id_attr;
        Rule<ast::Value()> simplevalue_;
        Rule<ast::Id(std::string element_name)> expr_open;
        Rule<void(std::string element_name)> expr_close;

        Rule<ast::expression(std::string element_name )> subexpr_;

        // compounds
        Rule<ast::addition()>       addition_;
        Rule<ast::subtraction()>    subtraction_;
        Rule<ast::multiplication()> multiplication_;
        Rule<ast::division()>       division_;
        Rule<ast::expression()>     expression_;

        Rule<ast::expressions()> 
            expressions_;
    };

} /*parser*/

namespace eval {
    using namespace ast;

    struct machine : static_visitor<Value> {
        // convenience interface
        Value evaluate(expression const& e) const {
            return apply_visitor(*this, e);
        }
        
        // accepts
        Value operator()(Value       const& v) const { return v; }
        Value operator()(subtraction const& e) const { return evaluate(e.minuend)  - evaluate(e.subtrahend); }
        Value operator()(division    const& e) const { return evaluate(e.dividend) / evaluate(e.divisor);    }

        Value operator()(addition const& e) const {
            return accumulate( e.items, Value{}, 
                    [this](Value v,expression const& i){ return v + evaluate(i); });
        }

        Value operator()(multiplication const& e) const {
            return accumulate( e.factors, Value{1}, 
                    [this](Value v,expression const& i){ return v * evaluate(i); });
        }
    };
}

static inline ast::Id get_id(ast::expression const& e) {
    return apply_visitor(ast::get_id_(), e);
}

using Result  = std::pair<int, ast::Value>;
using Results = std::map <int, ast::Value>;
using It      = boost::spirit::istream_iterator;

int main()
{
    std::ifstream ifs("expressions.xml");
    It f(ifs >> std::noskipws), l;

    try {
        ast::expressions parsed;

        grammar<It> g;
        // parsing
        bool ok = phrase_parse(f, l, g, qi::space, parsed);

        // output results
        if (ok)
        {
            eval::machine machine;

            std::cout << "<expressions>\n";
            for (auto& expr : parsed)
                if (get_id(expr))
                    std::cout << "\t<result id=\"" << *get_id(expr) << "\">" << machine.evaluate(expr) << "</result>\n";
            std::cout << "</expressions>\n";
        }
    } catch(qi::expectation_failure<It> const& e) {
        std::cout << "Expected " << e.what_ << " at '" << std::string(e.first,e.last) << "'\n";
    }
}

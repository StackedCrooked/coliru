#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/variant/recursive_wrapper.hpp>
#include <boost/lexical_cast.hpp>

namespace qi    = boost::spirit::qi;
namespace karma = boost::spirit::karma;
namespace phx   = boost::phoenix;

struct op_or  {};
struct op_and {};
struct op_xor {};
struct op_not {};

typedef std::string var;
template <typename tag> struct combination_op;
template <typename tag> struct unop;

typedef boost::variant<var, 
        boost::recursive_wrapper<unop <op_not> >, 
        boost::recursive_wrapper<combination_op<op_and> >,
        boost::recursive_wrapper<combination_op<op_xor> >,
        boost::recursive_wrapper<combination_op<op_or> >
        > expr;

template <typename tag> struct combination_op 
{ 
    typedef std::vector<expr> operands_t;
    combination_op() = default;
    combination_op(operands_t const& operands) : operands(operands) { }
    operands_t operands;
};

template <typename tag> struct unop  
{ 
    unop() = default;
    unop(const expr& o) : operand(o) { }
    expr operand; 
};

//////////////////////////////////////////////////
// Evaluation
struct eval : boost::static_visitor<bool> 
{
    eval() {}

    //
    bool operator()(const var& v) const 
    { 
        if (v=="T" || v=="t" || v=="true" || v=="True")
            return true;
        else if (v=="F" || v=="f" || v=="false" || v=="False")
            return false;
        return boost::lexical_cast<bool>(v); 
    }

    bool operator()(const combination_op<op_and>& b) const
    {
        return std::accumulate(begin(b.operands), end(b.operands), true, 
                [this](bool a, expr const& b) { return a && recurse(b); });
    }
    bool operator()(const combination_op<op_xor>& b) const
    {
        return std::accumulate(begin(b.operands), end(b.operands), false, 
                [this](bool a, expr const& b) { return a != recurse(b); });
    }
    bool operator()(const combination_op<op_or>& b) const
    {
        return std::accumulate(begin(b.operands), end(b.operands), false, 
                [this](bool a, expr const& b) { return a || recurse(b); });
    }
    bool operator()(const unop<op_not>& u) const
    {
        return !recurse(u.operand);
    } 

    private:
    template<typename T>
        bool recurse(T const& v) const 
        { return boost::apply_visitor(*this, v); }
};

bool evaluate(const expr& e)
{ 
    return boost::apply_visitor(eval(), e); 
}

//////////////////////////////////////////////////
// Parser grammar
template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, expr(), Skipper>
{
    parser() : parser::base_type(expr_)
    {
        using namespace qi;

        or_  = no_case [ "OR"  ] > '(' > expr_list > ')';
        xor_ = no_case [ "XOR" ] > '(' > expr_list > ')';
        and_ = no_case [ "AND" ] > '(' > expr_list > ')';
        not_ = no_case [ "NOT" ] > expr_;
        var_ = qi::lexeme[ +alpha ];

        expr_list = +expr_;
        expr_ = xor_ | and_ | or_ | not_ | var_;

        on_error<fail> ( expr_, std::cout
             << phx::val("Error! Expecting ") << _4 << phx::val(" here: \"")
             << phx::construct<std::string>(_3, _2) << phx::val("\"\n"));
    }

  private:
    template <typename Attr> using Rule = qi::rule<It, Attr(), Skipper>;
    Rule<var>                    var_;
    Rule<unop<op_not>>           not_;
    Rule<combination_op<op_and>> and_;
    Rule<combination_op<op_xor>> xor_;
    Rule<combination_op<op_or>>  or_;
    Rule<std::vector<expr>>      expr_list;
    Rule<expr>                   expr_;
};

//////////////////////////////////////////////////
// Output generator
template <typename It>
    struct generator : karma::grammar<It, expr()>
{
    generator() : generator::base_type(expr_)
    {
        using namespace karma;

        or_  = lit("OR ")  << '(' << expr_list[ _1 = phx::bind(&combination_op<op_or >::operands, _val) ] << ')';
        xor_ = lit("XOR ") << '(' << expr_list[ _1 = phx::bind(&combination_op<op_xor>::operands, _val) ] << ')';
        and_ = lit("AND ") << '(' << expr_list[ _1 = phx::bind(&combination_op<op_and>::operands, _val) ] << ')';
        not_ = lit("NOT ") << expr_;
        var_ = karma::string;

        expr_list = expr_ % ' ';
        expr_ = var_ | not_ | xor_ | and_ | or_ | not_;
    }

  private:
    template <typename Attr> using Rule = karma::rule<It, Attr()>;
    Rule<var>                    var_;
    Rule<unop<op_not>>           not_;
    Rule<combination_op<op_and>> and_;
    Rule<combination_op<op_xor>> xor_;
    Rule<combination_op<op_or>>  or_;
    Rule<std::vector<expr>>      expr_list;
    Rule<expr>                   expr_;
};

int main()
{
    const std::string input("xor (and (true F) or (and (T T) and (F T)));");

    auto f(std::begin(input)), l(std::end(input));
    const static parser<decltype(f)> p;

    expr result;
    bool ok = qi::phrase_parse(f,l,p > ';',qi::space,result);

    if (!ok)
        std::cout << "invalid input\n";
    else
    {
        const static generator<boost::spirit::ostream_iterator> g;
        std::cout << "tree: " << karma::format(g, result) << "\n";
        std::cout << "eval: " << evaluate(result) << "\n";
    }

    if (f!=l) std::cout << "unparsed: '" << std::string(f,l) << "'\n";
}

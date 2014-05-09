#define BOOST_SPIRIT_USE_PHOENIX_V3 //ADDED
#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/variant/recursive_wrapper.hpp>

namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;

struct op_rule {};
struct op_sum  {};
struct op_prod {};
struct op_seq  {};
struct op_atom {};
struct symb_epsilon {};


typedef std::string var;
template <typename tag> struct binop;
template <typename tag> struct unop;
template <typename tag> struct symb;

typedef boost::variant<var, 
        boost::recursive_wrapper<symb <symb_epsilon> >, 
        boost::recursive_wrapper<unop <op_atom> >, 
        boost::recursive_wrapper<unop <op_seq> >, 
        boost::recursive_wrapper<binop<op_rule> >,
        boost::recursive_wrapper<binop<op_sum> >,
    boost::recursive_wrapper<binop<op_prod> >
        > expr;

template <typename tag> struct binop 
{ 
    explicit binop(const expr& l, const expr& r) : oper1(l), oper2(r) { }
    expr oper1, oper2;
    
    friend std::ostream& operator<<(std::ostream& os, binop)
    {   return os; }
};

template <typename tag> struct unop  
{ 
    explicit unop(const expr& o) : oper1(o) { }
    expr oper1; 
    
    friend std::ostream& operator<<(std::ostream& os, unop)
    {   return os; }
};

template <typename tag> struct symb
{ 
    explicit symb() { }
    
    friend std::ostream& operator<<(std::ostream& os, symb)
    {   return os; }
};

// struct printer : boost::static_visitor<void>
// {
//     printer(std::ostream& os) : _os(os) {}
//     std::ostream& _os;
// 
//     //
//     void operator()(const var& v) const { _os << v; }
// 
//     void operator()(const binop<op_and>& b) const { print(" & ", b.oper1, b.oper2); }
//     void operator()(const binop<op_or >& b) const { print(" | ", b.oper1, b.oper2); }
//     void operator()(const binop<op_xor>& b) const { print(" ^ ", b.oper1, b.oper2); }
// 
//     void print(const std::string& op, const expr& l, const expr& r) const
//     {
//         _os << "(";
//             boost::apply_visitor(*this, l);
//             _os << op;
//             boost::apply_visitor(*this, r);
//         _os << ")";
//     }
// 
//     void operator()(const unop<op_not>& u) const
//     {
//         _os << "(";
//             _os << "!";
//             boost::apply_visitor(*this, u.oper1);
//         _os << ")";
//     }
// };

// std::ostream& operator<<(std::ostream& os, const expr& e)
// { boost::apply_visitor(printer(os), e); return os; }

template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, expr(), Skipper>
{
    parser() : parser::base_type(expr_)
    {
        using namespace qi;

        expr_  = rule_.alias();

        rule_ = (var_ >> "="  >> sum_ ) [ _val = phx::construct<binop<op_rule> >(_1, _2) ] | sum_   [ _val = _1 ];
        sum_  = (prod_ >> "+" >> sum_)  [ _val = phx::construct<binop<op_sum>  >(_1, _2) ] | prod_  [ _val = _1 ];
        prod_ = (seq_ >> "." >> prod_)  [ _val = phx::construct<binop<op_prod> >(_1, _2) ] | seq_   [ _val = _1 ];
        seq_  = ("Seq" > simple     )   [ _val = phx::construct<unop <op_seq>  >(_1)     ] | atom_  [ _val = _1 ];
	atom_ = ("Z" > var_         )   [ _val = phx::construct<unop <op_atom> >(_1)     ] | eps_   [ _val = _1 ];
	eps_  = lit("E" ) /*CHANGED*/                 [ _val = phx::construct<symb <symb_epsilon> >()/*CHANGED*/    ] | simple [ _val = _1 ];

        simple = (('(' > expr_ > ')') | var_);
        var_ = qi::lexeme[ +alpha ];

        BOOST_SPIRIT_DEBUG_NODE(expr_);
        BOOST_SPIRIT_DEBUG_NODE(rule_);
        BOOST_SPIRIT_DEBUG_NODE(sum_);
        BOOST_SPIRIT_DEBUG_NODE(prod_);
        BOOST_SPIRIT_DEBUG_NODE(seq_);
        BOOST_SPIRIT_DEBUG_NODE(atom_);
        BOOST_SPIRIT_DEBUG_NODE(eps_);
        BOOST_SPIRIT_DEBUG_NODE(simple);
        BOOST_SPIRIT_DEBUG_NODE(var_);
    }

  private:
    qi::rule<It, var() , Skipper> var_;
  qi::rule<It, expr(), Skipper> expr_, rule_, sum_, prod_, seq_, atom_, eps_, simple;
};

int main()
{
  std::string input = "B = Z(1) + Z(2).Z(2).C";
  /*for (auto& input : (std::list<std::string>) {
            // From the OP:
            "(a and b) xor ((c and d) or (a and b));",
            "a and b xor (c and d or a and b);",

            /// Simpler tests:
            "a and b;",
            "a or b;",
            "a xor b;",
            "not a;",
            "not a and b;",
            "not (a and b);",
            "a or b or c;",
            })*/
    {
        auto f(std::begin(input)), l(std::end(input));
        parser<decltype(f)> p;

        try
        {
            expr result;
            bool ok = qi::phrase_parse(f,l,p > ';',qi::space,result);

            if (!ok)
                std::cerr << "invalid input\n";
            else
	      std::cout << "result: ";// << result << "\n";

        } catch (const qi::expectation_failure<decltype(f)>& e)
        {
            std::cerr << "expectation_failure at '" << std::string(e.first, e.last) << "'\n";
        }

        if (f!=l) std::cerr << "unparsed: '" << std::string(f,l) << "'\n";
    }

    return 0;
}

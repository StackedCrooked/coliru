#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/variant/recursive_wrapper.hpp>
#include <boost/lexical_cast.hpp>

namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;

struct op_or  {};
struct op_and {};
struct op_not {};

typedef std::string var; 
template <typename tag> struct binop;
template <typename tag> struct unop;

typedef boost::variant<var, 
        boost::recursive_wrapper<unop <op_not> >, 
        boost::recursive_wrapper<binop<op_and> >,
        boost::recursive_wrapper<binop<op_or> >
        > expr;

template <typename tag> struct binop
{
    explicit binop(const expr& l, const expr& r) : oper1(l), oper2(r) { }
    expr oper1, oper2;
};

template <typename tag> struct unop
{
    explicit unop(const expr& o) : oper1(o) { }
    expr oper1;
};

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

    bool operator()(const binop<op_and>& b) const
    {
        return recurse(b.oper1) && recurse(b.oper2);
    }
    bool operator()(const binop<op_or>& b) const
    {
        return recurse(b.oper1) || recurse(b.oper2);
    }
    bool operator()(const unop<op_not>& u) const
    {
        return !recurse(u.oper1);
    } 

    private:
    template<typename T>
        bool recurse(T const& v) const 
        { return boost::apply_visitor(*this, v); }
};

struct printer : boost::static_visitor<void> 
{
    printer(std::ostream& os) : _os(os) {}
    std::ostream& _os;

    //
    void operator()(const var& v) const { _os << v; }

    void operator()(const binop<op_and>& b) const { print(" & ", b.oper1, b.oper2); }
    void operator()(const binop<op_or >& b) const { print(" | ", b.oper1, b.oper2); }

    void print(const std::string& op, const expr& l, const expr& r) const
    {
        _os << "(";
        boost::apply_visitor(*this, l);
        _os << op;
        boost::apply_visitor(*this, r);
        _os << ")";
    }

    void operator()(const unop<op_not>& u) const
    {
        _os << "(";
        _os << "!";
        boost::apply_visitor(*this, u.oper1);
        _os << ")";
    } 
};

bool evaluate(const expr& e) 
{ return boost::apply_visitor(eval(), e); }

std::ostream& operator<<(std::ostream& os, const expr& e) 
{ boost::apply_visitor(printer(os), e); return os; }

    template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, expr(), Skipper>
{
        parser() : parser::base_type(expr_)
        {
            using namespace qi;

            expr_  = or_.alias();

            or_  = (and_ >> '|'  >> or_ ) [ _val = phx::construct<binop<op_or > >(_1, _2) ] | and_   [ _val = _1 ];
            and_ = (not_ >> '&' >> and_)  [ _val = phx::construct<binop<op_and> >(_1, _2) ] | not_   [ _val = _1 ];
            not_ = ('!' > simple       )  [ _val = phx::construct<unop <op_not> >(_1)     ] | simple [ _val = _1 ];

            simple = (('(' > expr_ > ')') | var_);
            var_ = qi::lexeme[ +(alpha|digit) ];

            BOOST_SPIRIT_DEBUG_NODE(expr_);
            BOOST_SPIRIT_DEBUG_NODE(or_);
            BOOST_SPIRIT_DEBUG_NODE(and_);
            BOOST_SPIRIT_DEBUG_NODE(not_);
            BOOST_SPIRIT_DEBUG_NODE(simple);
            BOOST_SPIRIT_DEBUG_NODE(var_);
        }

        private:
        qi::rule<It, var() , Skipper> var_;
        qi::rule<It, expr(), Skipper> not_, and_, or_, simple, expr_; 
};

int main() 
{
    const std::string inputs[] = { 
        std::string("true & false;"),
        std::string("true & !false;"),
        std::string("!true & false;"),
        std::string("true | false;"),
        std::string("true | !false;"),
        std::string("!true | false;"),

        std::string("T&F;"),
        std::string("T&!F;"),
        std::string("!T&F;"),
        std::string("T|F;"),
        std::string("T|!F;"),
        std::string("!T|F;"),
        std::string("") // marker
    };

    for (const std::string *i = inputs; !i->empty(); ++i)
    {
        typedef std::string::const_iterator It;
        It f(i->begin()), l(i->end());
        parser<It> p;

        try
        {
            expr result;
            bool ok = qi::phrase_parse(f,l,p > ';',qi::space,result);

            if (!ok)
                std::cerr << "invalid input\n";
            else
            {
                std::cout << "result:\t" << result << "\n";
                std::cout << "evaluated:\t" << evaluate(result) << "\n";
            }

        } catch (const qi::expectation_failure<It>& e)
        {
            std::cerr << "expectation_failure at '" << std::string(e.first, e.last) << "'\n";
        }

        if (f!=l) std::cerr << "unparsed: '" << std::string(f,l) << "'\n";
    }

    return 0; 
}

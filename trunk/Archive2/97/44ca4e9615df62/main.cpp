#include <vector>
#include <string>
#include <iostream>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/variant/recursive_wrapper.hpp>
#include <functional>

namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;

int m = 0;
std::vector<std::vector<int> > formules;

struct op_or  {};
struct op_and {};
struct op_not {};
struct op_impl {};

typedef int var;
template <typename tag> struct binop;
template <typename tag> struct unop;

typedef boost::variant<var,
               boost::recursive_wrapper<unop <op_not> >,
               boost::recursive_wrapper<binop<op_and> >,
               boost::recursive_wrapper<binop<op_or> >,
               boost::recursive_wrapper<binop<op_impl> >
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

struct tseitin : boost::static_visitor<void> {
    tseitin() {}

    void operator()(const var &v, int p = 0) const {
        m++;
        std::vector<int> tmp;
        tmp.push_back(-m);
        tmp.push_back((int)v);
        formules.push_back(tmp);
        tmp.clear();
        tmp.push_back(m);
        tmp.push_back(-(int)v);
    }
    void operator()(const binop<op_and>  &b, int p = m++) const { proceed(0, b.oper1, b.oper2, p); }
    void operator()(const binop<op_impl> &b, int p = m++) const { proceed(2, b.oper1, b.oper2, p); }
    void operator()(const binop<op_or>   &b, int p = m++) const { proceed(1, b.oper1, b.oper2, p); }
    void operator()(const unop<op_not>   &u, int p = m++) const {
        int p1 = m + 1;
        m += 1;
        std::vector<int> tmp;
        tmp.push_back(-p);
        tmp.push_back(-p1);
        formules.push_back(tmp);
        tmp.clear();
        tmp.push_back(p);
        tmp.push_back(p1);
        formules.push_back(tmp);
        recurse(u.oper1, p1);
    }

    void proceed(int nop, const expr &l, const expr &r, int p) const {
        int p1 = m + 1;
        int p2 = m + 2;
        m += 2;
        std::vector<int> tmp;
        if (nop == 0) // and operator
        {
            tmp.push_back(-p);
            tmp.push_back(p1);
            formules.push_back(tmp);
            tmp.clear();
            tmp.push_back(-p);
            tmp.push_back(p2);
            formules.push_back(tmp);
            tmp.clear();
            tmp.push_back(p);
            tmp.push_back(-p1);
            tmp.push_back(-p2);
            formules.push_back(tmp);
        } else if (nop == 1) // or operator
        {
            tmp.push_back(-p);
            tmp.push_back(p1);
            tmp.push_back(p2);
            formules.push_back(tmp);
            tmp.clear();
            tmp.push_back(p);
            tmp.push_back(-p1);
            formules.push_back(tmp);
            tmp.clear();
            tmp.push_back(p);
            tmp.push_back(-p2);
            formules.push_back(tmp);
        }
        recurse(l, p1);
        recurse(r, p2);
    }

  private:
    template <typename T, typename U> void recurse(T const &v, U p) const {
        boost::apply_visitor(std::bind(*this, std::placeholders::_1, p), v);
    }
};


struct printer : boost::static_visitor<void>
{
    printer(std::ostream& os) : _os(os) {}
    std::ostream& _os;

    //
    void operator()(const var& v) const { _os << v;}

    void operator()(const binop<op_and>& b) const { print(" & ", b.oper1, b.oper2); }
    void operator()(const binop<op_or >& b) const { print(" | ", b.oper1, b.oper2); }
    void operator()(const binop<op_impl>& b) const { print(" => ", b.oper1, b.oper2); }

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

std::ostream& operator<<(std::ostream& os, const expr& e)
{ boost::apply_visitor(printer(os), e); return os; }

template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, expr(), Skipper>
{
    parser() : parser::base_type(expr_)
    {
        using namespace qi;

        expr_  = impl_.alias();

        impl_= (or_ >> "=>" >> impl_)   [ _val = phx::construct<binop<op_impl>>(_1,_2) ] | or_    [ _val = _1 ];
        or_  = (and_ >> "\\/"  >> or_ ) [ _val = phx::construct<binop<op_or >>(_1, _2) ] | and_   [ _val = _1 ];
        and_ = (not_ >> "/\\" >> and_)  [ _val = phx::construct<binop<op_and>>(_1, _2) ] | not_   [ _val = _1 ];
        not_ = ("~" > simple       )    [ _val = phx::construct<unop <op_not>>(_1)     ]     | simple [ _val = _1 ];

        simple = (('(' > expr_ > ')') | var_);
        //  var_ = *as_string[qi::lexeme[ +digit ]] [if_(phx::ref(m) < _1) [phx::ref(m) = _1], _val = _1]; // qi::lexeme[ +digit ] [count++];//lexeme[ +alpha ];
        var_ = int_ [_val = _1, if_(phx::ref(m) < _1) [phx::ref(m) = _1]];
    }

  private:
    qi::rule<It, var() , Skipper> var_;
    qi::rule<It, expr(), Skipper> not_, and_,  or_, impl_, simple, expr_;
};

int main()
{
    for (auto& input : std::list<std::string> {
        "(1 /\\ 2) \\/ (~3 /\\ (4 \\/ 5))",
        "1 /\\ 2",
        "2 \\/ 3",
        "~3",
        "4",
        "100 /\\ 2 \\/ 3 => ~4",
    })
    {
        auto f(std::begin(input)), l(std::end(input));
        parser<decltype(f)> p;

        try
        {
            expr result;
            bool ok = qi::phrase_parse(f,l,p,qi::space,result);

            if (!ok)
                std::cerr << "invalid input\n";
            else
            {
                std::cout << "result: " << result << "\n";
                std::cout << "count : " << m << "\n";
                boost::apply_visitor(std::bind(tseitin(), std::placeholders::_1, 0), result);
                for(size_t i = 0; i < formules.size(); i++)
                {
                    for(size_t j = 0; j < formules[i].size(); j++)
                        std::cout << formules[i][j] << " ";
                    std::cout << std::endl;
                }
                m = 0;
            }

        } catch (const qi::expectation_failure<decltype(f)>& e)
        {
            std::cerr << "expectation_failure at '" << std::string(e.first, e.last) << "'\n";
        }

        if (f!=l) std::cerr << "unparsed: '" << std::string(f,l) << "'\n";
    }

    return 0;
}


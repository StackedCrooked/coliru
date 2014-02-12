#define BOOST_SPIRIT_USE_PHOENIX_V3

#include<fstream>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/variant/recursive_wrapper.hpp>

namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;

typedef std::string var;
template <typename tag> struct binop;
template <typename tag> struct unop;

typedef boost::variant<var,double, 
        // Logical Operators
        boost::recursive_wrapper<binop<struct op_equ> >, 
        boost::recursive_wrapper<unop <struct op_not> >, 
        boost::recursive_wrapper<binop<struct op_and> >, 
        boost::recursive_wrapper<binop<struct op_xor> >, 
        boost::recursive_wrapper<binop<struct op_or>  >, 
        
        // /*Airthemetic Operators*/
        boost::recursive_wrapper<binop<struct op_plus>  >, 
        boost::recursive_wrapper<binop<struct op_minus> >, 
        boost::recursive_wrapper<binop<struct op_mul>   >, 
        boost::recursive_wrapper<binop<struct op_div>   >, 
        boost::recursive_wrapper<binop<struct op_mod>   >, 
        
        // /*Relational Operators*/
        boost::recursive_wrapper<binop<struct op_gt>  >, 
        boost::recursive_wrapper<binop<struct op_lt>  >, 
        boost::recursive_wrapper<binop<struct op_gte> >, 
        boost::recursive_wrapper<binop<struct op_lte> >, 
        boost::recursive_wrapper<binop<struct op_eq> >,
        boost::recursive_wrapper<binop<struct op_ne> >
        
       // boost::recursive_wrapper<binop<op_prop> >
    > expr;

template <typename tag> struct binop 
{ 
    //explicit binop(const expr& l, const std::string& c, const expr& r) : oper1(l), oper2(r), op(c) { }
     explicit binop(const expr& l,  const expr& r) : oper1(l), oper2(r) { }
    expr oper1, oper2; 
    //std::string op;
};

template <typename tag> struct unop  
{ 
    explicit unop(const expr& o) : oper1(o) { }
    expr oper1; 
};

struct signal_definition   {
    std::string name; expr value; 
    friend std::ostream& operator<<(std::ostream& os, signal_definition const& sd) {
        return os << sd.name << " := " << sd.value;
    }
};
struct property_assignment {
    std::string signal, property, value_ident; 
    friend std::ostream& operator<<(std::ostream& os, property_assignment const& pa) {
        return os << pa.signal << '.' << pa.property << " := " << pa.value_ident;
    }
};

BOOST_FUSION_ADAPT_STRUCT(signal_definition, (std::string, name)(expr, value))
BOOST_FUSION_ADAPT_STRUCT(property_assignment, (std::string, signal)(std::string, property)(std::string, value_ident))

typedef boost::variant<signal_definition, property_assignment> statement;
typedef std::vector<statement> program;

struct printer : boost::static_visitor<void>
{
    printer(std::ostream& os) : _os(os) {}
    std::ostream& _os;
    
    void operator()(const var& v)             const { _os << v;  }
    void operator()(const double& val)        const { _os << val; }
    
    void operator()(const binop<op_and>& b)   const { print(" & ",  b.oper1, b.oper2); }
    void operator()(const binop<op_or >& b)   const { print(" | ",  b.oper1, b.oper2); }
    void operator()(const binop<op_xor>& b)   const { print(" ^ ",  b.oper1, b.oper2); }
    void operator()(const binop<op_equ>& b)   const { print(" = ",  b.oper1, b.oper2); }
    
    void operator()(const binop<op_plus>& b)  const { print(" + ",  b.oper1, b.oper2); }
    void operator()(const binop<op_minus>& b) const { print(" - ",  b.oper1, b.oper2); }
    void operator()(const binop<op_mul>& b)   const { print(" * ",  b.oper1, b.oper2); }
    void operator()(const binop<op_div>& b)   const { print(" / ",  b.oper1, b.oper2); }
    void operator()(const binop<op_mod>& b)   const { print(" % ",  b.oper1, b.oper2); }
    
    void operator()(const binop<op_gt>& b)    const { print(" > ",  b.oper1, b.oper2); }
    void operator()(const binop<op_lt>& b)    const { print(" < ",  b.oper1, b.oper2); }
    void operator()(const binop<op_gte>& b)   const { print(" >= ", b.oper1, b.oper2); }
    void operator()(const binop<op_lte>& b)   const { print(" <= ", b.oper1, b.oper2); }
    void operator()(const binop<op_eq>& b)    const { print(" == ", b.oper1, b.oper2); }
    void operator()(const binop<op_ne>& b)    const { print(" != ", b.oper1, b.oper2); }
    
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
{ 
    boost::apply_visitor(printer(os), e); 
    return os; 
}

std::ostream& operator<<(std::ostream& os, const program& p)
{ 
    for (auto& stmt : p)
        os << stmt << ";\n";
    return os; 
}

template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, program(), Skipper>
{
    enum op_token { 
        TOK_PLUS, TOK_MINUS, TOK_DIV, TOK_MULT, TOK_MOD,
        TOK_LT, TOK_LTE, TOK_GT, TOK_GTE,
        TOK_EQ, TOK_NE,TOK_AND,TOK_OR,TOK_XOR
    };

    static expr make_binop(op_token discriminant, const expr& left, const expr& right)
    {
        switch(discriminant)
        {
            case TOK_PLUS:  return binop<op_plus>(left , right); // "+" ,
            case TOK_MINUS: return binop<op_minus>(left, right); // "-" ,
            case TOK_DIV:   return binop<op_div>(left  , right); // "/" ,
            case TOK_MULT:  return binop<op_mul>(left  , right); // "*" ,
            case TOK_MOD:   return binop<op_mod>(left  , right); // "%" ,
            case TOK_LT:    return binop<op_lt>(left   , right); // "<" ,
            case TOK_LTE:   return binop<op_lte>(left  , right); // "<=",
            case TOK_GT:    return binop<op_gt>(left   , right); // ">" ,
            case TOK_GTE:   return binop<op_gte>(left  , right); // ">" ,
            case TOK_EQ:    return binop<op_eq>(left   , right); // ">=",
            case TOK_NE:    return binop<op_ne>(left   , right); // "!" ,
            case TOK_AND:   return binop<op_and>(left  , right);
            case TOK_OR:    return binop<op_or>(left   , right);
            case TOK_XOR:   return binop<op_xor>(left  , right);
        }
        throw std::runtime_error("unreachable in make_binop");
    }
    
    parser() : parser::base_type(program_)
    {
        using namespace qi;

        program_    = *statement_;
        statement_  = (signal_def_ | prop_assgn_) >> ';';
        
        signal_def_ = ident_ >> ":=" >>  expr_;
        prop_assgn_ = ident_ >> lexeme ['.' >> raw [ prop_ ]] >> ":=" >>  ident_;

        expr_       = ( not_ >> binop_ >> expr_ )  [ _val = phx::bind(make_binop, qi::_2, qi::_1, qi::_3) ] 
                      | not_ [ _val = _1 ];
        not_        = ("NOT."  >> simple [ _val = phx::construct<unop <op_not> >(_1) ])
                    | (tdelay_ >> simple [ _val = phx::construct<unop <op_not> >(_1) ])
                    | simple [ _val = _1 ]
                    ;
                       
        tdelay_     = lexeme[ (lit("LE")|"FE") > double_ > -char_("mn") > "s." ];
        
        simple      =   ('(' > expr_ > ')') 
                      | ('[' > expr_ > ']') 
                      | ('{' > expr_ > '}') 
                      | lexeme[double_]
                      | ident_
                      ;
                      
        ident_      = char_("a-zA-Z_") >> *char_("a-zA-Z_0-9");
        
        BOOST_SPIRIT_DEBUG_NODES(
                (program_) (signal_def_) (prop_assgn_) (prop_name_)
                (expr_) (not_)
                (simple) (ident_) (tdelay_)
             )

        binop_.add
            ("-",  TOK_MINUS)
            ("+",  TOK_PLUS)
            ("/",  TOK_DIV)
            ("*",  TOK_MULT)
            ("%",  TOK_MOD)
            ("<",  TOK_LT)
            ("<=", TOK_LTE)
            (">",  TOK_GT)
            (">=", TOK_GTE)
            ("==", TOK_EQ)
            ("!=", TOK_NE)
            ("AND", TOK_AND)
            ("OR",  TOK_OR)
            ("XOR", TOK_XOR)
            ;
        prop_.add
            ("status",  true)
            ("expire",  true)
            ("collect", true)
            ("inhibit", true)
            ;
    }

  private:
    qi::symbols<char, op_token> binop_;
    qi::symbols<char, bool>     prop_;

    qi::rule<It, var()> ident_;
    qi::rule<It, expr(), Skipper> not_, simple, expr_, tdelay_;

    qi::rule<It, std::string()                > prop_name_;
    qi::rule<It, signal_definition(),  Skipper> signal_def_;
    qi::rule<It, property_assignment(),Skipper> prop_assgn_;
    qi::rule<It, statement(),          Skipper> statement_;
    qi::rule<It, program(),            Skipper> program_;
};

int main()
{
    std::ifstream fin("input.txt");
    std::stringstream buffer;
    buffer << fin.rdbuf();
    std::string input = buffer.str();
    fin.close();

    typedef std::string::const_iterator It;
    typedef qi::rule<It> Skip;
    It f(input.begin()), l(input.end());
    
    static const Skip skip = qi::space | "--" >> *(qi::char_ - qi::eol) >> qi::eol;
    static const parser<It, Skip> p;
    
    try
    {
        program result;
        bool ok = qi::phrase_parse(f, l, p, skip, result);

        if (!ok) std::cerr << "invalid input\n";
        else     std::cout << result << "\n";
        if (f!=l)
            std::cerr << "remaining unparsed input: '" << std::string(f,l) << "'\n";
    } 
    catch (const qi::expectation_failure<It>& e)
    {
        std::cerr << "Expectation Failure at '" << std::string(e.first, e.last) << "'" << std::endl;
    }
}

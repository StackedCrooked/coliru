
#define BOOST_SPIRIT_USE_PHOENIX_V3

#include<fstream>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/variant/recursive_wrapper.hpp>


namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;

// Logical Operators
struct op_or  {};
struct op_and {};
struct op_xor {};
struct op_not {};
struct op_equ {};

// Arithmetic Operators
struct op_plus  {};
struct op_minus {};
struct op_mul   {};
struct op_div   {};
struct op_mod   {};

// Relational Operators
struct op_gt  {};
struct op_lt  {};
struct op_gte {};
struct op_lte {};
struct op_eq  {};
struct op_ne  {};


typedef std::string var;
template <typename tag> struct binop;
template <typename tag> struct unop;

typedef boost::variant<var,double, 
        // Logical Operators
        boost::recursive_wrapper<binop<op_equ> >, 
		boost::recursive_wrapper<unop <op_not> >, 
		boost::recursive_wrapper<binop<op_and> >, 
		boost::recursive_wrapper<binop<op_xor> >, 
		boost::recursive_wrapper<binop<op_or>  >, 
        
		// /*Airthemetic Operators*/
		boost::recursive_wrapper<binop<op_plus>  >, 
		boost::recursive_wrapper<binop<op_minus> >, 
		boost::recursive_wrapper<binop<op_mul>   >, 
		boost::recursive_wrapper<binop<op_div>   >, 
		boost::recursive_wrapper<binop<op_mod>   >, 
        
		// /*Relational Operators*/
		boost::recursive_wrapper<binop<op_gt>  >, 
		boost::recursive_wrapper<binop<op_lt>  >, 
		boost::recursive_wrapper<binop<op_gte> >, 
		boost::recursive_wrapper<binop<op_lte> >, 
		boost::recursive_wrapper<binop<op_eq> >,
        boost::recursive_wrapper<binop<op_ne> >
        
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



template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, expr(), Skipper>
{
    enum op_token { 
        TOK_PLUS, TOK_MINUS, TOK_DIV, TOK_MULT, TOK_MOD,
        TOK_LT, TOK_LTE, TOK_GT, TOK_GTE,
        TOK_EQ, TOK_NE,TOK_AND,TOK_OR,TOK_XOR
    };
    enum props {
    PROP_TYPE,PROP_TEXT,PROP_INHIBIT,PROP_COLLECTOR
    };
    static expr make_binop(op_token discriminant, const expr& left, const expr& right)
    {
        switch(discriminant)
        {
            case TOK_PLUS:  return binop<op_plus>(left,    right);    // "+", 
            case TOK_MINUS: return binop<op_minus>(left,   right);    // "-", 
            case TOK_DIV:   return binop<op_div>(left,     right);    // "/", 
            case TOK_MULT:  return binop<op_mul>(left,     right);    // "*", 
            case TOK_MOD:   return binop<op_mod>(left,     right);    // "%", 
            case TOK_LT:    return binop<op_lt>(left,      right);    // "<", 
            case TOK_LTE:   return binop<op_lte>(left,     right);   // "<=",
            case TOK_GT:    return binop<op_gt>(left,      right);    // ">", 
            case TOK_GTE:   return binop<op_gte>(left,     right);    // ">", 
            case TOK_EQ:    return binop<op_eq>(left,      right);   // ">=",
            case TOK_NE:    return binop<op_ne>(left,      right);    // "!",        
            case TOK_AND:    return binop<op_and>(left,     right); 
            case TOK_OR:     return binop<op_or>(left,      right); 
            case TOK_XOR:    return binop<op_xor>(left,     right); 
        }
        throw std::runtime_error("unreachable in make_binop");
    }
    
    static expr make_binprop(op_token discriminant, const expr& left, const expr& right)
    {
        switch(discriminant)
        {
           case PROP_TYPE: return binop<op_eq>(left, right);
        }
        throw std::runtime_error("unreachable in make_binprop");
        
    }
    parser() : parser::base_type(start)
    {
        using namespace qi;

		start   =  (ident_ >> ":=" >  expr_)  [ _val = phx::construct<binop<op_equ> >(_1, _2) ] 
                  //| prop_ident_ //[ _val = _2 ]
                  ;
		expr_   = tok_.alias();
		tok_    = ( not_   >> binop_ >> tok_ )  [ _val = phx::bind(make_binop, qi::_2, qi::_1, qi::_3) ] 
                  | not_   [ _val = _1 ];
		not_    =  ("NOT."  >> simple [ _val = phx::construct<unop <op_not> >(_1) ]        
                   | simple [ _val = _1 ]  )
				   | (tdelay_  >> simple [ _val = phx::construct<unop <op_not> >(_1) ] 
				   | simple [ _val = _1 ]  )
				   ;
				   
	    tdelay_ = lexeme[ ( lit("tdt") | lit("tdf") ) > double_ > *char_("mn") > "s." ]  ;
		
		
        simple   =   ('('  > expr_ > ')') 
                   | ('['  > expr_ > ']') 
                   | ('{'  > expr_ > '}') 
                   | ident_ 
                   | lexeme[double_] ;
                   
		ident_   =  lexeme[ char_("a-zA-Z_") >> *char_("a-zA-Z_0-9")];
		
		prop_ident_ =  lexeme[ char_("a-zA-Z_") >> *char_("a-zA-Z_0-9")
                                               >>  prop_ 
                                               > ":=" 
                                               >  char_("a-zA-Z_") >> *char_("a-zA-Z_0-9") 
                                 ] 
                                 //[ _val = _2 ]
                                 ;
        
		BOOST_SPIRIT_DEBUG_NODE(start);
        BOOST_SPIRIT_DEBUG_NODE(expr_);
        BOOST_SPIRIT_DEBUG_NODE(tok_);
        BOOST_SPIRIT_DEBUG_NODE(not_);
        BOOST_SPIRIT_DEBUG_NODE(simple);
        BOOST_SPIRIT_DEBUG_NODE(ident_);
        BOOST_SPIRIT_DEBUG_NODE(prop_ident_);
		BOOST_SPIRIT_DEBUG_NODE(tdelay_);

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
            (".status",      PROP_TYPE)
            (".expire",      PROP_TEXT)

            ;
    }

  private:
    qi::symbols<char, op_token> binop_;
    qi::symbols<char, props> prop_;
	qi::rule<It, var() , Skipper> ident_, prop_ident_;
    qi::rule<It, expr(), Skipper> not_, tok_, simple, expr_, tdelay_;
	qi::rule<It, expr(), Skipper> start;
};

int main()
{

    std::ifstream fin("input.txt");
    std::stringstream buffer;
    buffer << fin.rdbuf();
    std::string input = buffer.str();
    fin.close();

    typedef std::string::const_iterator It;
    
    It f,l;
    f=input.begin();
    l=input.end();
    
    static const qi::rule<It> skip_ws_and_comments 
    = qi::space 
    | "--" >> *(qi::char_ - qi::eol) >> qi::eol
    ;

    static const parser<It, qi::rule<It> > p;
    
    while(f!=l)
    {

        try
        {
            expr result;

            bool ok = qi::phrase_parse(f
                    , l
                    , p > ';'
                    , skip_ws_and_comments
                    , result);

            if (!ok)
            {
                std::cerr << "invalid input\n";
                break;
            }
            else
            {
                std::cout << result << "\n\n\n";
            }
        } 
        catch (const qi::expectation_failure<It>& e)
        {
           
            std::cerr << "Expectation Failure at '" << std::string(e.first, e.last) << "'" << std::endl;
            break;
        }
    }
}

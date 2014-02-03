#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/variant/recursive_wrapper.hpp>
#include<fstream>
#include<vector>



namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;

//Logical Operators
struct op_or  {};
struct op_and {};
struct op_xor {};
struct op_not {};
struct op_equ {};

//Airthemetic Operators
struct op_plus {};
struct op_minus {};
struct op_mul {};
struct op_div {};
struct op_mod {};

//Relational Operators
struct op_gt {};
struct op_lt {};
struct op_gte {};
struct op_lte {};
struct op_eq {};

typedef std::string var;
template <typename tag> struct binop;
template <typename tag> struct unop;

typedef boost::variant<var,double, 
        //Logical Operators
		boost::recursive_wrapper<binop<op_equ> >,
        boost::recursive_wrapper<unop <op_not> >, 
        boost::recursive_wrapper<binop<op_and> >,
        boost::recursive_wrapper<binop<op_xor> >,
        boost::recursive_wrapper<binop<op_or> >,
		
		///*Airthemetic Operators*/
		boost::recursive_wrapper<binop<op_plus> >,
		boost::recursive_wrapper<binop<op_minus> >,
		boost::recursive_wrapper<binop<op_mul> >,
		boost::recursive_wrapper<binop<op_div> >,
		boost::recursive_wrapper<binop<op_mod> >,
		
		///*Relational Operators*/
		boost::recursive_wrapper<binop<op_gt> >,
		boost::recursive_wrapper<binop<op_lt> >,
		boost::recursive_wrapper<binop<op_gte> >,
		boost::recursive_wrapper<binop<op_lte> >,
		boost::recursive_wrapper<binop<op_eq> >
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

struct printer : boost::static_visitor<void>
{
    printer(std::ostream& os) : _os(os) {}
    std::ostream& _os;

    
    void operator()(const var& v) const { _os << v; }
    void operator()(const double& val) const { _os << val; }
    
    void operator()(const binop<op_and>& b) const { print(" & ", b.oper1, b.oper2); }
    void operator()(const binop<op_or >& b) const { print(" | ", b.oper1, b.oper2); }
    void operator()(const binop<op_xor>& b) const { print(" ^ ", b.oper1, b.oper2); }
	void operator()(const binop<op_equ>& b) const { print(" = ", b.oper1, b.oper2); }
	
	void operator()(const binop<op_plus>& b) const { print(" + ", b.oper1, b.oper2); }
	void operator()(const binop<op_minus>& b) const { print(" - ", b.oper1, b.oper2); }
	void operator()(const binop<op_mul>& b) const { print(" * ", b.oper1, b.oper2); }
	void operator()(const binop<op_div>& b) const { print(" / ", b.oper1, b.oper2); }
	void operator()(const binop<op_mod>& b) const { print(" % ", b.oper1, b.oper2); }
	
	
	void operator()(const binop<op_gt>& b) const { print(" > ", b.oper1, b.oper2); }
	void operator()(const binop<op_lt>& b) const { print(" < ", b.oper1, b.oper2); }
	void operator()(const binop<op_gte>& b) const { print(" >= ", b.oper1, b.oper2); }
	void operator()(const binop<op_lte>& b) const { print(" <= ", b.oper1, b.oper2); }
	void operator()(const binop<op_eq>& b) const { print(" == ", b.oper1, b.oper2); }
	
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



typedef BOOST_TYPEOF(qi::space | "--" >> *(qi::char_ - qi::eol) >> qi::eol) skipper_type;
template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, expr(), Skipper>
{
     static expr make_binop(char discriminant, const expr& left, const expr& right)
    {
        switch(discriminant)
        {
        case '+': return binop<op_plus>(left, right);
        case '-': return binop<op_minus>(left, right);
        case '/': return binop<op_div>(left, right);
        case '*': return binop<op_mul>(left, right);
        case '%': return binop<op_mod>(left, right);
        }
        throw std::runtime_error("unreachable in make_binop");
    }

    parser() : parser::base_type(start)
    {
        using namespace qi;

		start = (ident_ >> ":=" >>  expr_) [ _val = phx::construct<binop<op_equ> >(_1, _2) ] ;
		
        expr_  = mod_.alias();
        mod_ =  (or_ >> qi::char_("*/%+-")  >> mod_ ) [ _val = phx::bind(make_binop, qi::_2, qi::_1, qi::_3) ] | or_   [ _val = _1 ];

         
        or_  = (xor_ >> "OR"  >> or_ ) [ _val = phx::construct<binop<op_or > >(_1, _2) ] | xor_   [ _val = _1 ];
        xor_ = (and_ >> "XOR" >> xor_) [ _val = phx::construct<binop<op_xor> >(_1, _2) ] | and_   [ _val = _1 ];
        and_ = (not_ >> "AND" >> and_) [ _val = phx::construct<binop<op_and> >(_1, _2) ] | not_   [ _val = _1 ];
        not_ = ("NOT" > simple ) [ _val = phx::construct<unop <op_not> >(_1)     ] | simple [ _val = _1 ];

        simple = (('(' > expr_ > ')') | ident_ | lexeme[double_] );
        //var_ = qi::lexeme[ +alpha ];
		ident_ %=  qi::lexeme[qi::char_("a-zA-Z_") >> *qi::char_("a-zA-Z_0-9")];
		
		
		BOOST_SPIRIT_DEBUG_NODE(start);
        BOOST_SPIRIT_DEBUG_NODE(expr_);
        BOOST_SPIRIT_DEBUG_NODE(or_);
        BOOST_SPIRIT_DEBUG_NODE(xor_);
        BOOST_SPIRIT_DEBUG_NODE(and_);
        BOOST_SPIRIT_DEBUG_NODE(not_);
        BOOST_SPIRIT_DEBUG_NODE(simple);
       // BOOST_SPIRIT_DEBUG_NODE(var_);
		BOOST_SPIRIT_DEBUG_NODE(ident_);
         // BOOST_SPIRIT_DEBUG_NODE(number);
          // BOOST_SPIRIT_DEBUG_NODE(simp);
    }

  private:
	qi::rule<It, var() , Skipper > ident_;
   // qi::rule<It, var() , Skipper> var_;
    qi::rule<It, expr(), Skipper> not_, and_, xor_, or_, simple, expr_,simp;
	qi::rule<It, expr(), Skipper>  plus_,minus_,mul_,div_,mod_;
	qi::rule<It, expr(), Skipper> start;
    // qi::rule<It, double(), Skipper> number;
};




int main()
{

    
	
	std::ifstream fin("input.txt");
	std::stringstream buffer;
	buffer << fin.rdbuf();
	std::string input = buffer.str();
	fin.close();
    

        std::string::const_iterator f,l;
        f=input.begin();
        l=input.end();
        std::string strip;
       
        
        
                
        // ok = qi::phrase_parse(f
        // ,l
        // , +qi::char_
        // ,"--" >> *(qi::char_ - qi::eol) >> qi::eol
        // ,strip
        // );
                
        // std::cout << strip ;
        // f=strip.begin();
        // l=strip.end();
        

    typedef std::string::const_iterator It;
    
    qi::rule<It> skip_ws_and_comments 
        = qi::space 
        | "--" >> *(qi::char_ - qi::eol) >> qi::eol
        ;

    
		while(f!=l)
		{
         
            //parser<std::string::const_iterator, qi::rule<std::string::const_iterator> > p;
            parser<It, qi::rule<It> >  p;
            
            try
            {
                expr result;
                                
                bool ok = qi::phrase_parse(f
                ,l
                ,p > ';'
                ,skip_ws_and_comments
                ,result);

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
                std::cerr << "expectation_failure at '" << std::string(e.first, e.last) << "'" << std::endl;
                break;
            }


		}


    return 0;
}
//#define BOOST_SPIRIT_QI_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <iostream>
#include <string>
#include <utility>
#include <map>

#include <boost/spirit/include/qi.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp> //important if you want to use pair/map
#include <boost/foreach.hpp>

namespace client { namespace ast
{
    ///////////////////////////////////////////////////////////////////////////
    //  The AST
    ///////////////////////////////////////////////////////////////////////////
    struct nil {};
    struct seq;
    struct expression;
    
    typedef std::string var;
    typedef std::pair<var,expression> assignment;
    typedef std::map<var,expression> rule_map;
    
    struct atom
    {
        int number;
    };
    
    struct epsilon
    {
        int number;
    };

    typedef boost::variant<
            nil,
            var,
            atom,
            epsilon,
            boost::recursive_wrapper<seq>,
            boost::recursive_wrapper<expression>
        >
    operand;

    struct seq
    {
        operand operand_;
    };

    struct operation
    {
        char operator_;
        operand operand_;
    };

    struct expression
    {
        operand first;
        std::list<operation> rest;
    };
    

    // print function for debugging
    inline std::ostream& operator<<(std::ostream& out, nil) { out << "nil"; return out; }
}}
BOOST_FUSION_ADAPT_STRUCT(
    client::ast::atom,
    (int, number)
)

BOOST_FUSION_ADAPT_STRUCT(
    client::ast::epsilon,
    (int, number)
)

BOOST_FUSION_ADAPT_STRUCT(
    client::ast::seq,
    (client::ast::operand, operand_)
)

BOOST_FUSION_ADAPT_STRUCT(
    client::ast::operation,
    (char, operator_)
    (client::ast::operand, operand_)
)

BOOST_FUSION_ADAPT_STRUCT(
    client::ast::expression,
    (client::ast::operand, first)
    (std::list<client::ast::operation>, rest)
)



namespace client { namespace ast
{
    ///////////////////////////////////////////////////////////////////////////
    //  The AST Printer
    ///////////////////////////////////////////////////////////////////////////
    struct printer : boost::static_visitor<void>
    {
        void operator()(nil) const {}
        
        void operator()(const var& variable) const
        {
            std::cout << variable;
        }
        
        void operator()(const atom& val) const 
        {
            std::cout << "Z[" << val.number << "]";
        }
        
        void operator()(const epsilon& val) const 
        {
            std::cout << "E[" << val.number << "]";
        }
        
        void operator()(const seq& sequence) const 
        {
            std::cout << "Seq[";
            boost::apply_visitor(*this,sequence.operand_);
            std::cout << "]";
        }

        void operator()(operation const& x) const
        {
            std::cout << x.operator_ << ' ';
            boost::apply_visitor(*this, x.operand_);
            
        }

        void operator()(expression const& x) const
        {
            std::cout << "( ";
            boost::apply_visitor(*this, x.first);
            for(operation const& oper: x.rest)
            {
                std::cout << ' ' ;
                (*this)(oper);
            }
            std::cout << " )";
        }
        
        void operator()(assignment const& x) const
        {
            (*this)(x.second);
            std::cout << " -> " << x.first << std::endl;
        }
    };
    
    //You can simply not mark the methods as const (you won't be able to use temporary functors)
    struct z_counter : boost::static_visitor<void>
    {
        int n;
        z_counter():n(){}
        
        void operator()(nil)
        {}
        
        void operator()(var)
        {}
        
        void operator()(epsilon)
        {}
        
        void operator()(atom)
        {
            ++n;
        }
        
        void operator()(const seq& sequence)  
        {
            boost::apply_visitor(*this,sequence.operand_);
        }

        void operator()(operation const& x) 
        {
            boost::apply_visitor(*this, x.operand_);
        }
        
        void operator()(expression const& x)
        {
            boost::apply_visitor(*this, x.first);
            for(operation const& oper: x.rest)
            {
                (*this)(oper);
            }
        }
        
        void operator()(const assignment& x)
        {
           (*this)(x.second); 
        }
    };
    
    //Or pass your state in the constructor and store it in a reference (or pointer)
    struct e_counter : boost::static_visitor<void>
    {
        int& n;
        e_counter(int& num):n(num){}
        
        void operator()(nil) const
        {}
        
        void operator()(var) const
        {}
        
        void operator()(epsilon) const
        {
            ++n;
        }
        
        void operator()(atom) const
        {}
        
        void operator()(const seq& sequence) const
        {
            boost::apply_visitor(*this,sequence.operand_);
        }

        void operator()(operation const& x) const
        {
            boost::apply_visitor(*this, x.operand_);
        }
        
        void operator()(expression const& x) const
        {
            boost::apply_visitor(*this, x.first);
            for(operation const& oper: x.rest)
            {
                (*this)(oper);
            }
        }
        
        void operator()(const assignment& x) const
        {
           (*this)(x.second); 
        }
    };
}}

namespace client
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    using boost::phoenix::function;

    ///////////////////////////////////////////////////////////////////////////////
    //  Our error handler
    ///////////////////////////////////////////////////////////////////////////////
    struct error_handler_
    {
        template <typename, typename, typename>
        struct result { typedef void type; };

        template <typename Iterator>
        void operator()(
            qi::info const& what
          , Iterator err_pos, Iterator last) const
        {
            std::cout
                << "Error! Expecting "
                << what                         // what failed?
                << " here: \""
                << std::string(err_pos, last)   // iterators to error-pos, end
                << "\""
                << std::endl
            ;
        }
    };

    function<error_handler_> const error_handler = error_handler_();

    ///////////////////////////////////////////////////////////////////////////////
    //  Our symb grammar
    ///////////////////////////////////////////////////////////////////////////////
    template <typename Iterator, typename Skipper=ascii::blank_type>
    struct symb : qi::grammar<Iterator, ast::rule_map(), Skipper>
    {
        symb() : symb::base_type(start)
        {
            qi::char_type char_;
            qi::int_type int_;
            qi::attr_type attr;
            ascii::alpha_type alpha;
            ascii::alnum_type alnum;
            qi::eol_type eol;
            qi::_2_type _2;
            qi::_3_type _3;
            qi::_4_type _4;

            using qi::on_error;
            using qi::fail;
            
            start = assignment % eol;

            assignment = var > '=' > expression;

            expression =
                term
                >> *(char_('+') > term)
                ;

            term =
                factor
                >> *(char_('.') > factor)
                ;

            atom = 'Z' >> ( int_ | attr(0) );
            
            epsilon = 'E' >> ( int_ | attr(0) );
            
            seq = "Seq" > factor;
            
            var = alpha>>*alnum;

            factor =
                   ('(' > expression > ')')
                |   atom
                |   epsilon
                |   seq
                |   var
                ;

            // Debugging and error handling and reporting support.
            BOOST_SPIRIT_DEBUG_NODES((start)(assignment)(expression)(term)(factor)(atom)(epsilon)(seq)(var));

            

            // Error handling
            on_error<fail>(expression, error_handler(_4, _3, _2));
        }

        qi::rule<Iterator, ast::rule_map(), Skipper> start;
        qi::rule<Iterator, ast::assignment(), Skipper> assignment;
        qi::rule<Iterator, ast::expression(), Skipper> expression;
        qi::rule<Iterator, ast::expression(), Skipper> term;
        qi::rule<Iterator, ast::operand(), Skipper> factor;
        qi::rule<Iterator, ast::atom(), Skipper> atom;
        qi::rule<Iterator, ast::epsilon(), Skipper> epsilon;
        qi::rule<Iterator, ast::seq(), Skipper> seq;
        qi::rule<Iterator, ast::var()> var; //if you omit the skipper the rule is implicitly lexeme
    };
}

void print_rules(const client::ast::rule_map& rules)
{
    client::ast::printer print;
    for(const auto& rule : rules)
        print(rule);
}

int count_z(const client::ast::rule_map& rules)
{
    client::ast::z_counter count;
    for(const auto& rule : rules)
        count(rule);
        
    return count.n;
}

int count_e(const client::ast::rule_map& rules)
{
    int n=0;
    client::ast::e_counter count(n);
    for(const auto& rule : rules)
        count(rule);
        
    return n;
}

///////////////////////////////////////////////////////////////////////////////
//  Main program
///////////////////////////////////////////////////////////////////////////////
int
main()
{

    typedef std::string::const_iterator iterator_type;
    typedef client::symb<iterator_type> symb;

    std::string str;
    {
        str="PP = Z + L1 . R1 + L2 . R2 + L3 . R3 + Seq Z3 . Seq Z4\nL1 = Z10.Z9\nR1 = Z12.PP + E4";

        symb parser;        // Our grammar
        client::ast::rule_map rules;

        std::string::const_iterator iter = str.begin();
        std::string::const_iterator end = str.end();
        boost::spirit::ascii::blank_type blank;
        bool r = phrase_parse(iter, end, parser, blank, rules);

        if (r && iter == end)
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << "\nResult: " << std::endl;
            print_rules(rules);
            std::cout << "In these rules there are " << count_z(rules) << " Z." << std::endl;
            std::cout << "And " << count_e(rules) << " E." << std::endl;
            std::cout << "-------------------------\n";
        }
        else
        {
            std::string rest(iter, end);
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "-------------------------\n";
        }
    }

    return 0;
}
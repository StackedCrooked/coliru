//#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp> 
#include <boost/spirit/include/phoenix.hpp>

namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;

struct Code {};
struct Variables {};

void fPushIntCV (int my_number, Code& c, Variables& v)
{
    std::cout << "fPushIntCV: " << my_number << "\n";
}

template<class Iterator> 
struct _Calculator : public qi::grammar<Iterator> {                                                                                               

    _Calculator(Code& code_, Variables& variables_)
      : _Calculator::base_type(number),                                                                                                           
        code(code_),
        variables(variables_)                                                                                                                     
   {  
       number = 
             ( 
               ("0x" >> qi::int_parser<int, 16, 1>())
             | ("0b" >> qi::int_parser<int,  2, 1>())
             | ("0"  >> qi::int_parser<int,  8, 1>())
             | qi::int_ /* accepts "0" */) [phx::bind(&fPushIntCV, qi::_1, phx::ref(code), phx::ref(variables))]
           ;
   }

    qi::rule<Iterator> number, result; //and a whole bunch of other ones too                                                            
    qi::rule<Iterator,std::string()> variable;                                                                                      

    Code& code;                                                                                                    
    Variables& variables;                                                                                                          
};

typedef std::string::const_iterator It;
typedef _Calculator<It> Calculator;

int main()
{
    Code code;
    Variables variables;
    Calculator g(code, variables); 

    for (std::string const input : { "0", "0xef1A", "010", "0b10101" })
    {
        It f(input.begin()), l(input.end());

        if(qi::parse(f, l, g))
             std::cout << "Parse success ('" << input << "')\n";
        else std::cout << "Parse failed ('" << input << "')\n";

        if (f != l)
            std::cout << "Input remaining: '" << std::string(f, l) << "'\n";
    }
}

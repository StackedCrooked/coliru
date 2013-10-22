#include <iostream>
#include <string>

// #define BOOST_SPIRIT_DEBUG
// #define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
//if you are using fine-grained include files make sure you have
//#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace qi=boost::spirit::qi;
namespace ascii=boost::spirit::ascii;
namespace phx=boost::phoenix;

struct employee
{
    int age;
	std::string first_name;
	std::string last_name;
	double salary;
};

BOOST_FUSION_ADAPT_STRUCT
(
	employee,
	(int,age)
	(std::string,first_name)
	(std::string,last_name)
	(double,salary)
)

template <typename Iterator>
struct employee_parser : qi::grammar<Iterator, employee(), ascii::space_type>
{
    employee_parser() : employee_parser::base_type(start),text1("uninitialized")
    {
        using qi::int_;
        using qi::lit;
        using qi::double_;
        using qi::lexeme;
        using ascii::char_;

        using ascii::string;
        using namespace qi::labels;            
        using boost::phoenix::ref;
        using boost::phoenix::val;

        quoted_string %= (lexeme['"' >> +(char_ - '"') >> '"' ]) ;

        start %= (
            lit("employee")
            >> '{'
            >>  int_ >> ','
            >>  quoted_string [std::cout<<ref(text1)<<" \n",ref(text1) = _1]  >> ','
            >>  quoted_string >> ','
            >>  double_
            >>  '}'  )                
            ;
		BOOST_SPIRIT_DEBUG_NODES( (start)(quoted_string) );
    }

    qi::rule<Iterator, std::string(), ascii::space_type> quoted_string;
    qi::rule<Iterator, employee(), ascii::space_type> start;
    std::string text1;
};

int main()
{
	std::string test= "employee{ 30, \"Llon\", \"Esmiz\", 30000.0 }";
	employee_parser<std::string::const_iterator> parser;
	std::string::const_iterator iter=test.begin(),end=test.end();
	
	employee parsed_employee;
	
	bool result = qi::phrase_parse(iter,end,parser,ascii::space,parsed_employee);
	if(result && iter==end )
	{
		std::cout << "Success. Employee: " << parsed_employee.first_name << " " << parsed_employee.last_name << std::endl;
        std::cout << "The text captured by reference is: " << parser.text1 << std::endl;
	}
	else
	{
		std::cout << result << " There was an error, unparsed: " << std::string(iter,end) << std::endl;
	}
}
#include <iostream>
#include <string>
#include <vector>

#define BOOST_SPIRIT_DEBUG

#include <boost/spirit/include/qi_core.hpp>
#include <boost/spirit/include/qi_matches.hpp>
#include <boost/spirit/include/qi_attr.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

struct class_info
{
    class_info():abstract_(),static_(),final_(){}
	bool abstract_;
	bool static_;
	bool final_;
};

BOOST_FUSION_ADAPT_STRUCT
(
	class_info,
	(bool, abstract_)
	(bool, static_)
	(bool, final_)
)

namespace qi=boost::spirit::qi;

template <typename Parser>
void parse_triplet(const std::string& test, const Parser& parser)
{
	std::string::const_iterator iter=test.begin(), end=test.end();
	class_info parsed_class;
		
	bool result=qi::phrase_parse(iter,end,parser,qi::space,parsed_class);
	
	if(!result)
	{
		std::cout << "The triplet could not be parsed. Unparsed: " << std::string(iter,end) << std::endl;
	}
	else
	{
		if(iter==end)
		{
			std::cout << "A triplet was parsed." << std::endl;
			std::cout << parsed_class.abstract_ << parsed_class.static_ << parsed_class.final_ << std::endl;
		}
		else
		{
			std::cout << "A triplet was parsed, but part of the input remained unparsed." << std::endl;
			std::cout << parsed_class.abstract_ << parsed_class.static_ << parsed_class.final_ << std::endl;
			std::cout << "Unparsed: " << std::string(iter,end) << std::endl;
		}
	}

}


int main()
{
	std::vector<std::string> tests;
	tests.push_back("final abstract static");
	tests.push_back("final abstract");
	tests.push_back("static");
	tests.push_back("static abstract");
	qi::rule<std::string::const_iterator,bool(),qi::space_type> abstract1, abstract2, static1, static2, final1, final2;
	abstract1 = qi::matches[qi::lit("abstract")];
	abstract2 = qi::lit("abstract") >> qi::attr(true);
	static1 = qi::matches[qi::lit("static")];
	static2 = qi::lit("static") >> qi::attr(true);
	final1 = qi::matches[qi::lit("final")];
	final2 = qi::lit("final") >> qi::attr(true);
	
	BOOST_SPIRIT_DEBUG_NODES( (abstract1)(abstract2)(static1)(static2)(final1)(final2) );
	
	for(std::size_t cont=0; cont < tests.size(); ++cont)
	{
		std::cout << "USING MATCHES: " << tests[cont] << std::endl;
		parse_triplet(tests[cont],abstract1 ^ static1 ^ final1);
		std::cout << "USING EXPLICIT ATTRIBUTE: " << tests[cont] << std::endl;
		parse_triplet(tests[cont],abstract2 ^ static2 ^ final2);
		
		
	}
}
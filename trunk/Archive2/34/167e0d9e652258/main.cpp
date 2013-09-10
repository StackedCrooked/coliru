#include <iostream>
#include <string>
#include <vector>

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

struct class_info
{
    bool abstract;
	std::string name;
};

BOOST_FUSION_ADAPT_STRUCT
(
	class_info,
	(bool, abstract)
	(std::string, name)
)

namespace qi=boost::spirit::qi;


int main()
{
	std::vector<std::string> tests;
	tests.push_back("abstract class Abstract");
	tests.push_back("class NotAbstract");
	tests.push_back("Stupid class");
	tests.push_back("class AlsoNotAbstract bla");
	
	qi::rule<std::string::const_iterator,std::string()> identifier_rule = qi::alpha >> *qi::alnum;
	
	qi::rule<std::string::const_iterator,class_info(),qi::space_type> class_rule = qi::matches[qi::lit("abstract")] >> "class" >> identifier_rule;
	
	for(std::size_t cont=0; cont < tests.size(); ++cont)
	{
		std::string::const_iterator iter=tests[cont].begin(), end=tests[cont].end();
		
		class_info parsed_class;
		
		bool result=qi::phrase_parse(iter,end,class_rule,qi::space,parsed_class);
		
		if(!result)
		{
			std::cout << "A class could not be parsed. Unparsed: " << std::string(iter,end) << std::endl;
		}
		else
		{
			if(iter==end)
			{
				std::cout << "A class was parsed." << std::endl;
				std::cout << parsed_class.name << (parsed_class.abstract?" is ":" is not ") << "abstract." << std::endl;
			}
			else
			{
				std::cout << "A class was parsed, but part of the input remained unparsed." << std::endl;
				std::cout << parsed_class.name << (parsed_class.abstract?" is ":" is not ") << "abstract." << std::endl;
				std::cout << "Unparsed: " << std::string(iter,end) << std::endl;
			}
		}
		
	}
}
#include <iostream>

#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
#include <boost/spirit/include/qi_core.hpp>
#include <boost/spirit/include/qi_nonterminal.hpp>

namespace qi      = boost::spirit::qi;
namespace iso8859 = boost::spirit::iso8859_1;


int main( int argc, char* argv[] )
{
    using namespace qi;
    char_type char_;
    double_type double_;
    iso8859::space_type space;

    
	rule<std::string::const_iterator,std::string(),iso8859::space_type> string_rule = *char_;
	rule<std::string::const_iterator,std::vector<double>(),iso8859::space_type> doubles_rule = *double_;
	rule<std::string::const_iterator,std::string(),iso8859::space_type> quoted_string_rule = '"' >> *~char_('"') >> '"';
	
	BOOST_SPIRIT_DEBUG_NODES( (string_rule)(doubles_rule)(quoted_string_rule) );

	{
		std::string input = "normalString 10.0 1.5 1.0 1.0 1.0 1.0";
		std::string::const_iterator iter = input.cbegin();
		std::string::const_iterator end   = input.cend();
		
		std::cout << std::endl << "STRING-VECTOR_OF_DOUBLES" << std::endl;
		
		phrase_parse( iter, end,
						string_rule >> doubles_rule,
						space );
	}
	
	{
		std::string input = "normalString 10.0 1.5 1.0 1.0 1.0 1.0 \"quotedString\"";
		std::string::const_iterator iter = input.cbegin();
		std::string::const_iterator end   = input.cend();
		
		std::cout << std::endl << "STRING-VECTOR_OF_DOUBLES-QUOTED_STRING" << std::endl;
		
		phrase_parse( iter, end,
						string_rule >> doubles_rule >> quoted_string_rule,
						space );
	}


    return 0;
}
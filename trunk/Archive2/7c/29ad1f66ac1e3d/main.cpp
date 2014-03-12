#include <iostream>
#include <regex>


int main()
{
    try
    {
		std::regex(R"(0|[1-9])");
        std::cout << "Success" << std::endl;
	}
	catch( std::regex_error &e)
	{
		switch(e.code())
		{
			case std::regex_constants::error_collate:	
				std::cerr << "The expression contained an invalid collating element name."; 
				break;
			case std::regex_constants::error_ctype:	
				std::cerr << "The expression contained an invalid character class name."; 
				break;
			case std::regex_constants::error_escape:	
				std::cerr << "The expression contained an invalid escaped character, or a trailing escape."; 
				break;
			case std::regex_constants::error_backref:	
				std::cerr << "The expression contained an invalid back reference."; 
				break;
			case std::regex_constants::error_brack:	
				std::cerr << "The expression contained mismatched brackets ([ and ])."; 
				break;
			case std::regex_constants::error_paren:	
				std::cerr << "The expression contained mismatched parentheses (( and ))."; 
				break;
			case std::regex_constants::error_brace:	
				std::cerr << "The expression contained mismatched braces ({ and })."; 
				break;
			case std::regex_constants::error_badbrace:	
				std::cerr << "The expression contained an invalid range between braces ({ and })."; 
				break;
			case std::regex_constants::error_range:	
				std::cerr << "The expression contained an invalid character range."; 
				break;
			case std::regex_constants::error_space:	
				std::cerr << "There was insufficient memory to convert the expression into a finite state machine."; 
				break;
			case std::regex_constants::error_badrepeat:	
				std::cerr << "The expression contained a repeat specifier (one of *?+{) that was not preceded by a valid regular expression."; 
				break;
			case std::regex_constants::error_complexity:	
				std::cerr << "The complexity of an attempted match against a regular expression exceeded a pre-set level."; 
				break;
			case std::regex_constants::error_stack:	
				std::cerr << "There was insufficient memory to determine whether the regular expression could match the specified character sequence."; 
				break;
			default: std::cerr << "undfined error";
		}
	}
    
}
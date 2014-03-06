#include <boost/regex.hpp>
#include <iostream>

int main()
{
    boost::regex repeatRegex("<\\? repeat min=[0-9]+ max=[0-9]+ \\?>(.*)<\\? endrepeat \\?>");
    std::string theString = "<? repeat min=1 max=2 ?>[A-Z0-9]{6},<? endrepeat ?>100,USD,Washington";
    boost::sregex_token_iterator itr(theString.begin(), theString.end(), repeatRegex);
	boost::sregex_token_iterator end;

	std::cout << std::endl << theString << std::endl;
	for(; itr != end; ++itr)
	{
		std::cout << *itr << std::endl;
	}
}

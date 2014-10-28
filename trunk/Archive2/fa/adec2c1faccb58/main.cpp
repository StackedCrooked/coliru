#include <regex>
#include <iostream>

char const* trackData = "%B341111597242000^ISO/AMEX TEST             ^1412101000000000000000000000000?";
enum class CardIssuer { Unknown, AmericanExpress };

CardIssuer m_issuer;

void IdentifyIssuer()
{
    try {
	   // Assume unknown by default to handle failures.
	   m_issuer = CardIssuer::Unknown;
	
	   std::regex magStripe{R"(^%B(\d+)\^)"};
	   std::cout << "blah" << std::endl;
	   std::cmatch matches;
	
	   if (std::regex_search(trackData, matches, magStripe))
	   {
	      std::string const& pan = matches[1];
	      
	      std::cout << pan << std::endl;
	
	   }
	}
	catch( std::regex_error const& e )
	{
		std::cout << e.code() << std::endl;
	}
}

int main()
{
    IdentifyIssuer();
}
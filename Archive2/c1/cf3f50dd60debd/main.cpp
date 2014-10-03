#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

int main()
{
  std::string str_warning("Warning [source=Handler, code=Generic, description=Security (42256) has no definition available. Constructing order books with default depths (DirectBookDepth=10, ImpliedBookDepth=2).");
  
    std::size_t found_start = str_warning.find("Security (");
    std::size_t found_end = str_warning.find(") has no definition available. Constructing order books with default depths (DirectBookDepth=10, ImpliedBookDepth=2).");
    if (found_start!=std::string::npos && found_end!=std::string::npos)
    {
        try
    	{
    		int security_id = std::stoi(str_warning.substr(found_start+10,found_end-found_start-10));
            std::cout << "onWarning:" << str_warning.substr(found_start+10,found_end-found_start-10) << std::endl;
    		std::cout << "onWarning:" << security_id << std::endl;
    	}
    	catch(std::invalid_argument const&)
    	{
    		std::cout << "onWarning: tried to convert but failed: " << str_warning;
    	}
    }

   return 0;
}

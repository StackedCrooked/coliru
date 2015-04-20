#include <iostream>
#include <regex>
#include <string>
 
int main() 
{
    std::string example{"hello <match1>  <match2>    <match3>"};
	std::regex re{"<([^>]+)>"};
	std::regex_token_iterator<std::string::iterator> it{example.begin(), example.end(), re, 1};
	decltype(it) end{};
	while (it != end) {
        std::cout << "Current value: " << *it << std::endl;
        std::cout << "Post-fix increment returns: " << *(it++) << std::endl;
	}
	return 0;
}
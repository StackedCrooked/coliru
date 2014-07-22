#include <iostream>
#include <regex>
#include <string>
#include <algorithm>
#include <memory>

int main()
{
    std::regex re("[ ]{2,}");
	std::string str("text    rt e rr   r");
     std::string str2 = str;
	auto results_begin = std::sregex_iterator(str.begin(), str.end(), re);
	for (std::sregex_iterator i = results_begin; i != std::sregex_iterator(); ++i) {
		str2.replace(str2.find((*i).str()), (*i).str().size() , " ");
	}
	std::cout << str2;
}
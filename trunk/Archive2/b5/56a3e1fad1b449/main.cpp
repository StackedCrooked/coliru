#include <iostream>
#include <regex>
#include <string>

int main()
{
    std::regex re("<.*>.*<.*>");
	std::string str("<body>text</body>wewqew\n"
	                "<p>text2</p>asdad	");
	auto results_begin = std::sregex_iterator(str.begin(), str.end(), re);
	for (std::sregex_iterator i = results_begin; i != std::sregex_iterator(); ++i) {
		std::cout << (*i).str()<<"\n";
	}
}
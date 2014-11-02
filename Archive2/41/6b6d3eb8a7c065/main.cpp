// regex_search example
#include <iostream>
#include <string>
#include <regex>

int main()
{
    std::string s("this subject has a submarine as a subsequence");
	std::smatch m;
	std::regex e("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

	std::cout << "Target sequence: " << s << std::endl;
	std::cout << "Regular expression: /\\b(sub)([^ ]*)/" << std::endl;
	std::cout << "The following matches and submatches were found:" << std::endl;
	auto first = s.cbegin();
	auto last = s.cend();
	while (std::regex_search(first,last,m,e)) {
		for (auto x : m) std::cout << x<< " ";
		std::cout << std::endl;
		first = m.suffix().first;
	}

	return 0;
}
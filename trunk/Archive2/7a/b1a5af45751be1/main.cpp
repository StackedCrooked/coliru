#include <vector>
#include <string>
#include <sstream>
#include <iostream>

std::vector<std::string> tokenize(const std::string& str, const char delimiter, bool collapse_delimiters)
{
    std::vector<std::string> tokens;
	
	std::stringstream ss(str);
	std::string tmp;
	while (std::getline(ss, tmp, delimiter)) {
		if (!tmp.empty() || !collapse_delimiters)
			tokens.push_back(tmp);
	}
    
    // TEMPORARILY REMOVED
    
    // Is this right? I want an empty final token since there is a trailing
    // delimiter, and std::getline won't do that for me.
    //if (!collapse_delimiters && !str.empty() && str.back() == delimiter)
    //    tokens.push_back("");
    
	return tokens;
}

void print_tokens(std::string str, char delimiter, bool collapse)
{
    auto const tokens = tokenize(str, delimiter, collapse);
    
    std::cout << "Got " << tokens.size() << " tokens: " << std::endl;
    
    for (auto const c : tokens)
    {
        std::cout << "\tToken: " << c << std::endl;
    }
    
    std::cout << std::endl;
}

int main()
{
    print_tokens("0:4:1:335577090:1:1:352452736::", ':', false);
    print_tokens("0:4:1:335577090:1:1:352452736::", ':', true);
    print_tokens("0:4:1:335577090:1:1:352452736:p", ':', false);
    print_tokens("0:4:1:335577090:1:1:352452736:p", ':', true);
    print_tokens("0:4:1:335577090:1:1:352452736:p:", ':', false);
    print_tokens("0:4:1:335577090:1:1:352452736:p:", ':', true);
}
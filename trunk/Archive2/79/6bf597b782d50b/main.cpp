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
	
    //---- fix for zeeshan's problem ----//
    if (!collapse_delimiters && !str.empty() && str.back() == delimiter)
        tokens.push_back("");
    //-----------------------------------//
    
	return tokens;
}

int main()
{
    // N.B. empty final token in virtual interface data, which we should
    // support. (Although I'm curious as to why the TS on SB won't tell us
    // VLAN_ENABLED_STATE or VLAN_TAG_STATE? Ascertaining this will tell us
    // whether this bug is limited to SB or could feasibly pop up for existing
    // SP deployments.)
    const std::string str = "0:4:1:335577090:1:1:352452736::";
    std::cout << tokenize(str, ':', false).size() << '\n';     // expecting 9; without fix is 8 instead
}
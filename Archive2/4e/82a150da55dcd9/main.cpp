#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
using namespace std;

string trim(string const& str)
{
    size_t first = str.find_first_not_of(" \r\n\t");

    if (first == -1)
		return "";

	size_t last = str.find_last_not_of(" \r\n\t");

	return str.substr(first, last - first + 1);
}

void trimmedSplit(const string &str, vector<string>& stringVector, const string& delimiter)
{
	regex reg(delimiter);
	sregex_token_iterator iter(str.begin(), str.end(), reg, -1);
	sregex_token_iterator end;

	for (; iter != end; ++iter)
	{
		string tmp((string)(*iter));
		trim(tmp);
		stringVector.push_back(tmp);
	}
}


int main() 
{
	cout << trim("      	\n [hi there]     ") << ":";
	return 0;
}

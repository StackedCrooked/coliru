#include <iostream>
#include <regex>
#include <string>
using namespace std;
int main()
{
    //int year, dayOfYear, day;
	//std::string month, leftParenthesis, rightParenthesis;
	std::string ExampleString = "2013 336 (02 DEC) 04";

	regex pattern("\\s*(\\d+)\\s+(\\d+)\\s*\\((\\d+)\\s+(\\w+)\\)\\s*(\\d+)");

	// Matching single string
	std::smatch sm;
	if (std::regex_match(ExampleString, sm, pattern)) {
		if (sm[1].matched)
			cout << "year: " << sm[1].str() << endl;
		if (sm[2].matched)
			cout << "dayOfYear: " << sm[2].str() << endl;
		if (sm[3].matched)
			cout << "day: " << sm[3].str() << endl;
		if (sm[4].matched)
			cout << "month: " << sm[4].str() << endl;
		if (sm[5].matched)
			cout << "hour: " << sm[5].str() << endl;
	}

	// If your data contains multiple lines to parse, use this version
	for (sregex_iterator it(ExampleString.begin(), ExampleString.end(), pattern), end_it;
		it != end_it; ++it)
	{
		if ((*it)[1].matched)
			cout << "year: " << (*it)[1].str() << endl;
		if ((*it)[2].matched)
			cout << "dayOfYear: " << (*it)[2].str() << endl;
		if ((*it)[3].matched)
			cout << "day: " << (*it)[3].str() << endl;
		if ((*it)[4].matched)
			cout << "month: " << (*it)[4].str() << endl;
		if ((*it)[5].matched)
			cout << "hour: " << (*it)[5].str() << endl;
	}
}
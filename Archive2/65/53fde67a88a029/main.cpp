#include <iostream>
#include <regex>
#include <string>
using namespace std;
int main()
{
    int year, dayOfYear, day;
	std::string month, leftParenthesis, rightParenthesis;
	std::string ExampleString = "2013 336 (02 DEC) 04";

	regex pattern("\\s*(\\d+)\\s+(\\d+)\\s*\\((\\d+)\\s+(\\w+)\\)\\s*(\\d+)");
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
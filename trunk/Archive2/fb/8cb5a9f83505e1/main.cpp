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
		cout << "year: " << sm[1].str() << endl;		
		cout << "dayOfYear: " << sm[2].str() << endl;
		cout << "day: " << sm[3].str() << endl;
		cout << "month: " << sm[4].str() << endl;
		cout << "hour: " << sm[5].str() << endl;
	}
    
    cout << endl;
    cout << endl;
    
    ExampleString = "2013 336 (02 DEC) 04" "\n2014 336 (02 DEC) 04" "\n2015 336 (02 DEC) 04";

	// If your data contains multiple lines to parse, use this version
	for (sregex_iterator it(ExampleString.begin(), ExampleString.end(), pattern), end_it;
		it != end_it; ++it)
	{
		cout << "year: " << (*it)[1].str() << endl;
		cout << "dayOfYear: " << (*it)[2].str() << endl;
		cout << "day: " << (*it)[3].str() << endl;
		cout << "month: " << (*it)[4].str() << endl;
		cout << "hour: " << (*it)[5].str() << endl;
        cout << endl;
	}
}
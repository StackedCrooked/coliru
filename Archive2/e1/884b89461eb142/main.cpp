#include <iostream>
#include <string>
#include <regex>

namespace tr1{}
namespace std{using namespace tr1;}

using namespace std;
using namespace std::regex_constants;

int main()
{
    std::string basePartOfSymbol = "CN H2012";
    //std::string basePartOfSymbol = "2012 ";

	const std::regex basePartRegExp("^(\\w+) (?:((?:(?:[FGHJKMNQUVXZ])(?:\\d{4}|\\d{2}|(?!\\d)))|(?:(?:\\d{4}|\\d{2}|\\d)(?:[FGHJKMNQUVXZ])))(\\d{0,2})|(\\d+W\\d+))(\\-\\w+)?(=\\w)?$");
    //const std::regex basePartRegExp("(\\d{4}|\\d{2}) ");

	std::smatch captures;
	const std::string symbol_str(basePartOfSymbol);
	std::regex_search(symbol_str, captures, basePartRegExp);

	cout << captures.size() << endl;

	int size = captures.size();

	for (int i = 0; i < size; ++i)
	{
		cout << i << ": " << captures.str(i) << endl;
	}

	return 0;
}
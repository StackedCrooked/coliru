#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main()
{
    std::string basePartOfSymbol = "%ES 1!-ENC";
    
    const std::regex basePartRegExp("^%(\\w+)?( )?(((\\d{1,2})|(\\w+))?(!)?)?((?:\\-([^=]*))?(?:=(.*))?)?(.+)?$");
    
    std::smatch captures;
    const std::string symbol_str(basePartOfSymbol);
	std::regex_search(symbol_str, captures, basePartRegExp);
    
    cout << captures.size() << endl;
    
    int size = captures.size();
    
    for (int i = 0; i < size; ++i)
    {
        cout << i << ": " << captures.str(i) << endl;
    }
    
}
#include <iostream>
#include <string>
#include <regex>

namespace tr1{}
namespace std{using namespace tr1;}

using namespace std;

int main()
{
    std::string basePartOfSymbol = "1!";
    
    //const std::regex basePartRegExp("^%(\\w+)?( )?(((\\d{1,2})|(\\w+))?(!)?)?((?:\\-([^=]*))?(?:=(.*))?)?(.+)?$");
    const std::regex basePartRegExp("^((\\d{1,2})|(\\w+))!");
    
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
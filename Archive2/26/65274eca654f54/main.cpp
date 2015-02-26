#include <iostream>
#include <string>
#include <regex>

namespace tr1{}
namespace std{using namespace tr1;}

using namespace std;
using namespace std::regex_constants;

int main()
{
    std::string basePartOfSymbol = "1!";
    
    const std::regex basePartRegExp("^(\\d{1,2})|(\\w+)!", match_continuous);
    
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
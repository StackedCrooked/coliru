#include <map>
#include <functional>
#include <string>
#include <algorithm>

using namespace std;

namespace Bill
{
    enum CodeCurrency
    {
        A, B, C
    };
    
    typedef map<CodeCurrency, string> currecny_code_map_t;
    currecny_code_map_t const& currency_code_map()
    {
        static currecny_code_map_t m;
        return m;
    }
}

struct IsCurrency : binary_function<pair<const Bill::CodeCurrency, string>, string, bool> {
    bool operator()(const pair<const Bill::CodeCurrency, string>& element, const string& expected) const {
        return element.second == expected;
    }
};

int main()
{

string currency = "RUB";
map<Bill::CodeCurrency, string>::const_iterator my_currency = find_if(Bill::currency_code_map().begin(), Bill::currency_code_map().end(), bind2nd(IsCurrency(), currency));  /// <--- ERROR IS HERE

}
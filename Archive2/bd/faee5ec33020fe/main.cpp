#include <iostream>
#include <regex>
using namespace std;

void match_print(const string &str, const regex &reg)
{
    bool match = regex_match(str, reg);
    cout << (match ? "match" : "not match") << endl;    
}



int main()
{
    match_print(string("11/04/2014"), regex(".*/.*/.*"));
    match_print(string("<key>cvaPortfolioLid</key>"), regex("<(.*)>.*</\\1>"));
    return 0;
}
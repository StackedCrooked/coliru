#include <regex>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    regex dorp(".*PolicyAndKeys.*");
    string url("UnitTest/PolicyAndKeys//UnitTest?authorizedParty=UnitTest");

    smatch match;
    regex_search(url, match, dorp);
    cout << "Match size: " << match.size() << endl;

    cout << "Matched: " << regex_match(url, dorp) << endl;
}
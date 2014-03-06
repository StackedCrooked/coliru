#include <iostream>
#include <regex>
using namespace std;
int main()
{
    string s = "|   | | |-DeclRefExpr 0x5d91218 <col:5> 'int' lvalue Var 0x5d91120 'y' 'int'";

    const regex r("(.*> )'(.*)'(.*)'(.*)'(.*)'(.*)'");  
    smatch sm;

    string result[6];
    if (regex_search(s, sm, r))
    {
        for (int i=0; i<6; i++)
        {
            result[i] =  sm[i+1];
        }
    }

    cout << result[0] << endl;
    cout << result[1] << endl;
    cout << result[2] << endl;
    cout << result[3] << endl;
    cout << result[4] << endl;
    cout << result[5] << endl;

    return 0;
}
#include <iostream>
#include <regex>
using namespace std;
int main()
{
    string s = "|   | | |-DeclRefExpr 0x5d91218 <col:5> 'int' lvalue Var 0x5d91120 'y' 'int'";

	const regex r("(.*)'(.*)'(.*)'(.*)'(.*)'(.*)'");  
	smatch sm;

	if (regex_search(s, sm, r))
	{
		for (int i=1; i<sm.size(); i++)
		{
			cout << sm[i] << endl;
		}
	}

	return 0;
}
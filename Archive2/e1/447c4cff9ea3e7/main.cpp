#include <iostream>
#include <regex>
using namespace std;
int main()
{
    string var = "first second third forth";

	const regex r("(.*) (.*) (.*) (.*)");  
	smatch sm;

	if (regex_search(var, sm, r))
	{
		for (int i=1; i<sm.size(); i++)
		{
			cout << sm[i] << endl;
		}
	}

	return 0;
}
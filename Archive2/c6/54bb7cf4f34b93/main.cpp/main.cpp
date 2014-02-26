#include <iostream>
#include <regex>
using namespace std;
int main()
{
    string s = "<rule source=\"192.168.10.10:any\" destination=\"any:any\" protocol=\"UDP\"/>";
 
	const regex r(".*\"(.*)\" destination.*");  
	smatch sm;
 
	string result;
	if (regex_search(s, sm, r))
		result =  sm[1];
 
	cout << result << endl; // result = "192.168.10.10:any"
 
	return 0;
}
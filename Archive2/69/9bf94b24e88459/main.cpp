#include <regex>
#include <string>
#include <iostream>

int main()
{
    using namespace std;

string str = "    1     10      0       11        3       11";
regex rx("\\d+");
cmatch res;

regex_search(str.c_str(), res, rx);

cout << res[1]<< endl;
cout << res.size()<< endl;

}
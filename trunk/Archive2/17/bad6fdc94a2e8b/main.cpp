#include <iostream>
#include <string>
#include <regex>
using namespace std;
int main()
{
    string s;
    cin>>s;
    if(regex_match(s,regex(R"(.*h{1,}e{1,}l{2,}o.*)"))) cout<<"YES";
    else cout<<"NO";
}
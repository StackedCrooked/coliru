#include<iostream>
#include<regex>
using namespace std;
int main()
{
    string s = "data-FileName-author-data-";
    string r = "(.+-){1}FileName-(.+-){2}";
    cout<<regex_match(s, regex(r))<<"\n"; //returns 0
}
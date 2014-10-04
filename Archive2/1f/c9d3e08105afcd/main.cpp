#include <iostream>
#include <string>
#include <regex>
using namespace std;
int main(){
    string s("abcd");
    smatch m;
    regex rgx("a(b(.+))");
    if(regex_match(s,m,rgx))
        for(const auto& sub : m)
            cout<<sub.str()<<endl;
}
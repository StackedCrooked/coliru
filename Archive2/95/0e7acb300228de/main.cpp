#include<unordered_set>
#include<iostream>
#include<utility>
#include<string>
#include<set>

using namespace std;

int main()
{
    set<pair<string, string> > g;
    pair<string, string> tmp;
    tmp.first="hello";
    tmp.second="world";
    g.insert(tmp);
}
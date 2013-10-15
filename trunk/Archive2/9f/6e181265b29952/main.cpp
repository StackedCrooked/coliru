#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

double val(string const& a)
{
    double rval = 0.0;
    for (char c:a) rval += c;
    return rval/a.size();
}

bool comp(string const& a, string const& b)
{
    return (val(a)<val(b));
}

int main()
{
    vector<string> vec;
    string str;
    while (cin >> str) vec.push_back(str);
    stable_sort(vec.begin(), vec.end(), comp);
    for (string& s : vec) cout << s << endl;
}

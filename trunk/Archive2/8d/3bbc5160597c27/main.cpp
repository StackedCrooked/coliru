#include <iostream>
#include <string>
#include <regex>

using namespace std;
 
int main()
{
    string str = "zzxayyzz";
    regex re1(".*(a|xayy)"); // ECMA
    regex re2(".*(a|xayy)", std::regex::extended); // POSIX
 
    cout << "Searching for .*(a|xayy) in zzxayyzz:\n";
    smatch m;
    regex_search(str, m, re1);
    cout << " ECMA (depth first search) match: " << m[0] << '\n';
    regex_search(str, m, re2);
    cout << " POSIX (leftmost longest)  match: " << m[0] << '\n';
}
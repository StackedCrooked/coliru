#include <iostream>
#include <string>
#include <regex>
 
int main()
{
    std::string str = "$(booga)";
    std::regex re1("\\$\\([a-zA-Z0-9_]+\\)"); // ECMA
//    std::regex re2("\\$\\(\\w+\\)", std::regex::extended); // POSIX
 
    std::cout << "Searching for .*(a|xayy) in zzxayyzz:\n";
    std::smatch m;
    std::regex_search(str, m, re1);
    std::cout << " ECMA (depth first search) match: " << m[0] << '\n';
//    std::regex_search(str, m, re2);
//    std::cout << " POSIX (leftmost longest)  match: " << m[0] << '\n';
}
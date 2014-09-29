#include <iostream>
#include <regex>
 
int main()
{
    std::locale::global(std::locale("en_US.UTF-8"));
    std::wstring str = L"AÀÁÂÃÄÅaàáâãäå";
    std::wregex re(L"a*", std::regex::basic);
    std::cout << std::boolalpha << std::regex_match(str, re) << '\n';
}
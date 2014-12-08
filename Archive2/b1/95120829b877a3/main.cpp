#include <iostream>
#include <string>
#include <regex>
#include <iterator>

int main ()
{
    std::wstring s = L"Αγοράσαμε από τον παντοπώλη λάδι πού αξίζει 245,8 δρχ. σαπούνι πού αξίζει 94 δρχ. και ρύζι πού αξίζει 11,75 δρχ. "
                      "Πόσα ρέστα θα πάρωμε από τα 7/8 των 50 δρχ.;";

    std::wregex e1(L"[0-9](.*)");
    std::wregex e2(L"(0-9)");

    std::wregex id(L"0[xX]");

    if( !std::regex_match(s,e1) ) std::cout << "e1 match: not matched\n";
    if( std::regex_search(s,e1) ) std::cout << "e1 search: found\n";
    if( !std::regex_search(s,e2) ) std::cout << "e2 search: not found\n";
    if( !std::regex_search(s,id) ) std::cout << "id search: not found\n";
}

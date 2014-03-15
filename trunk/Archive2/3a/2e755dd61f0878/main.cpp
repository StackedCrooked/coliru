#include <locale>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
 
int main()
{
    std::wcout.imbue(std::locale(""));
    std::vector<std::wstring> v = {L"r", L"t", L"P", L"c", L"O",
                                   L"Y", L"7"};
 
    std::wcout << "Default locale collation order: ";
    std::sort(v.begin(), v.end());
    for (auto s : v) std::wcout << s << ' '; std::wcout << '\n';
 
    std::wcout << "English locale collation order: ";
    std::sort(v.begin(), v.end(), std::locale("en_US.UTF-8"));
    for (auto s : v) std::wcout << s << ' '; std::wcout << '\n';
 
  //  std::wcout << "Swedish locale collation order: ";
//    std::sort(v.begin(), v.end(), std::locale("sv_SE.UTF-8"));
  //  for (auto s : v) std::wcout << s << ' '; std::wcout << '\n';
}
#include <regex>
#include <string>
#include <iostream>
 
int main()
{
    const std::wstring str = L"We bought the grocer oil worth 2,48 drachmas. "
                              "soap worth 94 drs. and rice worth 11,75 drachmas."
                              "How much change will take from 7/8 of 50 drachmas?"; 
                              
    std::wregex num(L"\\b([0-9]*),([0-9]*)");
    
    auto iter = std::wsregex_iterator( str.begin(), str.end(), num );
    const auto end = std::wsregex_iterator();
 
    for( ; iter != end; ++iter) std::wcout << iter->str() << L'\n' ;
}
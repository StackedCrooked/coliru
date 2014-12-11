#include <regex>
#include <string>
#include <iostream>
 
int main()
{
    const std::wstring str = L"We bought the grocer oil worth 2,48 drachmas. "
                              "soap worth 94 drs. and rice worth 11,75 drachmas."
                              "How much change will take from 7/8 of 50 drachmas?"; 
                              
    std::wregex integer(L"\\s[0-9]+\\s"); // whitespace, one or more dcimal digits, whitespace
    
    auto iter = std::wsregex_iterator( str.begin(), str.end(), integer );
    const auto end = std::wsregex_iterator();
    
    int sum = 0 ;
    for( ; iter != end; ++iter) 
    {
        std::wcout << iter->str() << L'\n' ;
        sum += std::stoi( iter->str() ) ; 
    }
    std::cout << "----\n" << sum << '\n' ;
}
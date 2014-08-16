#include <iostream>
#include <regex>
#include <string>
#include <cstring>

int main()
{
    std::regex r{R"([\[\]\{\}\(\)])"};
    char const *str = "asdf{ asdf }";
    {
    std::cmatch results;
    
    if(std::regex_search(str, results, r)) {
        std::cout << "match found\n";
    }
    }
    {
        std::cmatch results;
        
        auto first = std::cregex_iterator(str, str + std::strlen(str), r);
        auto last = std::cregex_iterator();
    
        if(first != last) std::cout << "match found\n";
        while(first != last) {
            std::cout << (*first++).str() << '\n';
        }
    }
}

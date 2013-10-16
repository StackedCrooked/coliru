#include <regex>
#include <iterator>
#include <iostream>
#include <string>
 
int main()
{
    const std::string s = "Quick brown fox.";
 
    std::regex words_regex("[^\\s]+");
    auto words_begin = 
        std::sregex_iterator(s.begin(), s.end(), words_regex);
    auto words_end = std::sregex_iterator();
 
    std::cout << "Found " 
              << std::distance(words_begin, words_end) 
              << " words:\n";
 
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;                                                 
        std::string match_str = match.str(); 
        std::cout << match_str << '\n';
    }   
}
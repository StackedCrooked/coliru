#include <regex>
#include <iterator>
#include <iostream>
#include <string>
 
int main()
{
    const std::string s
       = "freq10:20, freq11:27,    freq12:78, freq20:34, freq21:56, freq22:79";
 
    std::regex words_regex("( *,)?freq[0-9]+:([0-9]+)");
    auto words_begin = 
        std::sregex_iterator(s.begin(), s.end(), words_regex);
    auto words_end = std::sregex_iterator();
 
    std::cout << "Found " 
              << std::distance(words_begin, words_end) 
              << " frequencies:\n";
 
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        if (match.size() > 2) {
            std::string match_str = match[2]; 
            std::cout << match_str << '\n';
        }
    }
}
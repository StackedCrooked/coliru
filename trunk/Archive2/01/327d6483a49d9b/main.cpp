#include <regex>
#include <iterator>
#include <iostream>
#include <string>

int main()
{
    const std::string s = "??Quick!! - - + + brown ... fox.%^&%&^%";

    std::regex words_regex("[a-zA-Z]+");
    auto words_begin =
        std::sregex_iterator(s.begin(), s.end(), words_regex);
    auto words_end = std::sregex_iterator();

    std::cout << "Found "
              << std::distance(words_begin, words_end)
              << " words:\n";

    std::string match_suffix;

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
        std::string match_prefix = match.prefix();
        match_suffix = match.suffix();
        std::cout << "NO MATCH : " << match_prefix << '\n';
        std::cout << "MATCH    : " << match_str    << '\n';
    }
    std::cout << "NO MATCH : " << match_suffix << '\n';
}

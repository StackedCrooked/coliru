#include <iostream>
#include <string>
#include <regex>

struct regex_tokens {
    regex_tokens(std::sregex_token_iterator const& begin) : _begin(begin) {}
    regex_tokens(std::regex const& pattern, std::string const& target) : _begin(target.begin(), target.end(), pattern) {}
    
    std::sregex_token_iterator& begin(void) { return _begin; }
    std::sregex_token_iterator const& end(void) const { return _end; }

private:
    std::sregex_token_iterator        _begin;
    static std::sregex_token_iterator _end;
};

int main()
{
    std::string src = "0..100";
    std::regex comma_pattern(",");
    std::regex range_pattern("([0-9\\.\\-\\+]+|\\*)\\.\\.([0-9\\.\\-\\+]+|\\*)");
    
    for (auto token : regex_tokens(comma_pattern, src)) {
        std::smatch m;
        if (std::regex_match(token.str(), m, range_pattern)) {
            std::cout << "this is range: " << m[0].str() << " to " << m[1].str() << std::endl;
        }
        else {
            std::cout << "this is not range" << token << std::endl;
        }
    }
}

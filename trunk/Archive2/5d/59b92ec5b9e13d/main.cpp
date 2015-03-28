#include <string>
#include <regex>
#include <iostream>

int main()
{
    std::string s{R"(
tХB:Username!Username@Username.tcc.domain.com Connected
tХB:Username!Username@Username.tcc.domain.com WEBMSG #Username :this is a message
tХB:Username!Username@Username.tcc.domain.com Status: visible
)"};

    std::regex rgx("WEBMSG #([a-zA-Z0-9]+) :(.*)");
    std::smatch matches;

    if(std::regex_search(s, matches, rgx)) {
        std::cout << "Match found\n";
        
        for (size_t i = 0; i < matches.size(); ++i) {
            std::cout << i << ": '" << matches[i].str() << "'\n";
        }
    } else {
        std::cout << "Match not found\n";
    }
}

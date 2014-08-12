#include <string>
#include <regex>

int main()
{
    std::regex r("some(.*)regex(.*)here", std::regex_constants::egrep);
    std::string s("some(.*)regex(.*)here");
    std::regex r2(s, std::regex_constants::egrep);
}
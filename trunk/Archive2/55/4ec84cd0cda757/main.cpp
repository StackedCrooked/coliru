
#include <iostream>
#include <regex>

int main()
{
    std::string s1 = "WUBWEWUBAREWUBWUBTHEWUBCHAMPIONSWUBMYWUBFRIENDWUB";
    std::regex target("WUB");
    std::string replacement = "";
    std::string s2 = std::regex_replace(s1, target, replacement);
    
    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
    
    return 0;
}
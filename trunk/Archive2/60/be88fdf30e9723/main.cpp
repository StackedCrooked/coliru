#include <iostream>
#include <string>
#include <regex>
 
int main()
{
    std::string str = "matn 123 matn 23";
 
    std::regex reg("\\d+");
    auto it =std::sregex_iterator(str.begin(), str.end(), reg);
 
    int sum=0;
    for (; it != std::sregex_iterator(); ++it) {
        sum +=std::stoi(it->str());
    }
 
    std::cout << sum << '\n';
}
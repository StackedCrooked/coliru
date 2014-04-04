#include <iostream>
#include <string>
#include <vector>
#include <regex>

int main()
{
    std::string str{"not it, it\x88 and not it."};
    std::regex pat{"it[\\x80-\\xff]"};
    std::smatch m;
    regex_search(str, m, pat);
    
    std::cout << m[0] << std::endl;
    return 0;
}
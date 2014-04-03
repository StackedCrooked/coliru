#include <iostream>
#include <string>
#include <vector>
#include <regex>

int main()
{
    std::string str{"not it, it\x88\x89 and not it\x90\x09. Pitch. \n And \"hidden\" it\xfe\xff"};
    std::regex pat{"it[\\x00-\\xff]{2,2}$"};
    for (std::sregex_iterator p(str.begin(), str.end(), pat); p!=std::sregex_iterator{}; ++p) {
        std::string mymatch = (*p)[0];
        std::cout << "0x" << std::hex <<  static_cast<unsigned>(0xff & mymatch[2])  << std::endl;
    }
    return 0;
}
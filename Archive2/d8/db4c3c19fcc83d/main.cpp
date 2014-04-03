#include <iostream>
#include <string>
#include <vector>
#include <regex>

int main()
{
    std::string str{"not it, it\x88 and not it. Pitch. \n And \"hidden\" it\xfe\n"};
    std::regex pat{"it[\\x80-\\xff]"};
    for (std::sregex_iterator p(str.begin(), str.end(), pat); p!=std::sregex_iterator{}; ++p) {
        std::string mymatch = (*p)[0];
        std::cout << "0x" << std::hex <<  static_cast<unsigned>(0xff & mymatch[2])  << std::endl;
    }
    return 0;
}
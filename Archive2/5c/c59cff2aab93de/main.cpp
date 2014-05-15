#include <iostream>
#include <string>
#include <regex>

int main()
{
    std::string str = "{hello";
    std::regex exp("^\\{.*");

    std::smatch sm;
    std::regex_match( str, sm, exp );

    std::cout << "sm.size() = " << sm.size() << '\n'
              << "sm[0] = '" << sm[0] <<  "'\n";
}

#include <regex>
#include <iostream>

int main()
{
    try
    {
        std::regex r("(^|\n)#--[vgf]s\n", std::regex::extended);
    }
    catch(std::regex_error e) {
        std::cerr << e.what();
    }
}

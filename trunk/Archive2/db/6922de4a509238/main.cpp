#include <regex>
#include <iostream>

std::string fix(const std::string& in)
{
    return std::regex_replace(
        in,
        std::regex("(?:([a-zA-Z])([0-9]))|(?:([0-9])([a-zA-Z]))"),
        "\\1\\3 \\2\\4",
        std::regex_constants::format_sed
    );
}

int main()
{
    const std::string in[] = {
        "30EinsteinStreet",
        "548 Roe Drive5500 TestCity",
        "44B SaarlouisDrive1234Testtown"
    };
    
    for (auto el : in)
        std::cout << fix(el) << '\n';
}

/*
"30 EinsteinStreet"
"548 Roe Drive 5500 TestCity"
"44 B SaarlouisDrive 1234 Testtown"
*/

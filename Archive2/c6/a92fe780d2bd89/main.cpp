#include <iostream>
#include <regex>
#include <string>

void readCallbacks(const std::string & line)
{
    std::regex pattern("[a-z0-9]+\\(", std::regex_constants::icase);
    std::smatch result;

    if (regex_search(line, result, pattern, std::regex_constants::match_not_bol))
    {
        std::cout << result.str() << "\n";
    }
    else
    {
        std::cout << "No match\n";
    }
}

int main()
{
    	readCallbacks("Foo xyz123(yes)");
}
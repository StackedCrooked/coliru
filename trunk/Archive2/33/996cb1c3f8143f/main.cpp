#include <iostream>
#include <regex>
#include <string>

int main()
{
    // find the characters ei that follow a character other than c
    std::string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    std::regex r(pattern);
//  ~~~~~~~~~~~^~~~~~~~~~~ where the exception was thrown.
    std::smatch results;

    std::string test_str = "receipt freind theif receive";
    if (regex_search(test_str, results, r))
        std::cout << results.str() << std::endl;

    return 0;
}
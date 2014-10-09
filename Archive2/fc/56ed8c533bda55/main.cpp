#include <string>
#include <regex>
#include <iostream>

int main()
{
    std::string pattern("[[:alpha:]]*[^c]ei[[:alpha:]]*");
    std::regex r(pattern); 
    std::smatch results;   
    std::string test_str = "cei";

    if (std::regex_search(test_str, results, r)) 
        std::cout << results.str() << std::endl;      

    return 0;
}
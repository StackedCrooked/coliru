#include <string>
#include <iostream>
 
void print(std::string::size_type n, std::string const &s)
{
    if (n == std::string::npos) {
        std::cout << "not found\n";
    } else {
        std::cout << "found: " << s.substr(n) << '\n';
    }
}
 
const std::string KTestSuiteEventStart = "suite_config_started";
 
int main()
{
    std::string::size_type n;
    std::string const s = "prefix suite_config_started SuperPupperSuite";
    
    // search from beginning of string
    n = s.find(KTestSuiteEventStart);
    print(n, s);
 
    std::string testSuiteName = s.substr(n);

    std::cout << testSuiteName << std::endl;
    
    // ! Suggested code

    testSuiteName = s.substr(n + KTestSuiteEventStart.size());
    std::cout << "SUGGESTED variant: " << testSuiteName << std::endl;
}
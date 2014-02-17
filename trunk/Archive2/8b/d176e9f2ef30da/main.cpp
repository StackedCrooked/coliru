#include <iostream>
#include <string>
#include <regex>


int main () {
    std::cout << std::regex_replace ("there is a subsequence in the string", std::regex{R"(\bsub([^\s]+))"}, "sub-$1") << std::endl;
}
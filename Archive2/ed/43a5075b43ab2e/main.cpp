#include <regex>
#include <iostream>
#include <string>
#include <iterator>
 
int main() {
    using iterator_t = std::sregex_token_iterator;
    std::string const str{ "返回dpf9183h == D13D**&#@p9hLH8D91HAD1313D" };
    std::regex reg{ R"([\d=]*)" };
 
    std::copy(iterator_t{ str.cbegin(), str.cend(), reg }, iterator_t{}, std::ostream_iterator<std::string>{std::cout});
    std::cout << "\n";
 
    return 0;
}
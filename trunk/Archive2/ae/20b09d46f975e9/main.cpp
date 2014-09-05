#include <regex>
#include <iostream>

int main()
{
    std::string input = "Hello<Tag>blahblah</Tag> World";
    std::regex r1("<([a-zA-Z]+)>[a-z]+</\\1>");
    std::string result = regex_replace(input, r1, "");
    
    std::cout << "The result is '" << result << "'\n";
}
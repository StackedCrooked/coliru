#include <regex>
#include <iostream>

int main(int argc, const char * argv[]) {

    const std::string str = "foo bar ( foo bar baz quz";

    std::regex rgx("\\((.*)");
    std::smatch match;

    if (std::regex_search(str.begin(), str.end(), match, rgx)) {
        std::cout << match[1] << '\n';
    }

}
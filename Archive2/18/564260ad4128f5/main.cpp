#include <iostream>
#include <iterator>
#include <regex>
#include <vector>

int main() {
    std::string s = "{1, 2, 3, 4, 5}";

    std::istringstream iss{std::regex_replace(s, std::regex{R"(\{|\}|,)"}, " ")};
    std::vector<int> v{std::istream_iterator<int>{iss}, std::istream_iterator<int>{}};

    for (auto&& i : v) {
        std::cout << i << std::endl;
    }
}
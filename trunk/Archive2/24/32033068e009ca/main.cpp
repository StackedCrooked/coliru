#include <regex>

int main() {
    std::regex r("\\d\\s*?\\d");
    return std::regex_match("1     2", r);
}
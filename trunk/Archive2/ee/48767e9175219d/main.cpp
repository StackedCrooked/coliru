#include <regex>
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::regex_match;
using std::regex;

int main() {
    const string input("kleintierklinik");
    cout << "MATCH: " << regex_match(input, regex("klein.*")) << endl;
    cout << "MATCH: " << regex_match(input, regex("^klein.*")) << endl;
}
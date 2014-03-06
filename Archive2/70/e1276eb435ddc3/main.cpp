#include <regex>
#include <iostream>

using namespace std;

constexpr auto &text = R"(
XXXXXXXXXXXXXXXXXXXXXXXXXXXX"string1":"string2"XXXXXXXXXXXXXXXXXXXXXXXXXX"string3":"string4" XXXXXXXXXXXXXXXXXXXXXXXXXXXX...
XXXXXXXXXXXXXXXXXXXXXXXXXXXX"string5":"string6"XXXXXXXXXXXXXXXXXXXXXXXXXX"string7":"string8" XXXXXXXXXXXXXXXXXXXXXXXXXXXX...
)";

int main() {
    const regex pattern{R"~("([^"]*)":"([^"]*)")~"};
    cmatch pieces;
    constexpr auto e = text + sizeof(text) - 1;
    for (auto i = text; regex_search(i, e, pieces, pattern); i = pieces[0].second) {
        cout << pieces.format("First: $1, Second: $2") << endl;
    }
}
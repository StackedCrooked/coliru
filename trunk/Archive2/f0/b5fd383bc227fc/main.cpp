#include <regex>
#include <iostream>

using namespace std;

const string text = R"(
XXXXXXXXXXXXXXXXXXXXXXXXXXXX"string1":"string2"XXXXXXXXXXXXXXXXXXXXXXXXXX"string3"  :"string4" XXXXXXXXXXXXXXXXXXXXXXXXXXXX...
XXXXXXXXXXXXXXXXXXXXXXXXXXXX"string5":  "string6"XXXXXXXXXXXXXXXXXXXXXXXXXX"string7"  :  "string8" XXXXXXXXXXXXXXXXXXXXXXXXXXXX...
)";

int main() {
    const regex pattern{R"~("([^"]*)"\s*:\s*"([^"]*)")~"};
    for (auto it = sregex_iterator(begin(text), end(text), pattern); it != sregex_iterator(); ++it) {
        cout << it->format("First: $1, Second: $2") << endl;
    }
}
#include <regex>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

const string text = R"(
XXXXXXXXXXXXXXXXXXXXXXXXXXXX"string1":"string2"XXXXXXXXXXXXXXXXXXXXXXXXXX"string3":"string4" XXXXXXXXXXXXXXXXXXXXXXXXXXXX...
XXXXXXXXXXXXXXXXXXXXXXXXXXXX"string5":"string6"XXXXXXXXXXXXXXXXXXXXXXXXXX"string7":"string8" XXXXXXXXXXXXXXXXXXXXXXXXXXXX...
)";

int main() {
    const regex pattern{R"~("([^"]*)":"([^"]*)")~"};
    auto left_it = sregex_token_iterator(begin(text), end(text), pattern, 1);
    auto right_it = sregex_token_iterator(begin(text), end(text), pattern, 2);
    const auto end = sregex_token_iterator();

    while (left_it != end && right_it != end) {
        cout << "First: " << left_it->str()
             << ", Second: " << right_it->str() << endl;
        ++left_it;
        ++right_it;
    }
}

#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main() {
    regex e("(..)\\1");
    string s("aaaa");
    if (regex_match(s,e))
        cout << "match" << endl;
    return 0;
}
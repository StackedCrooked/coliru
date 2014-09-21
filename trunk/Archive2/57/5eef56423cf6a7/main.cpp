#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    vector<string> names = {"anh", "yeu", "em", "hon", "the"};
    sort(begin(names), end(names), [](const string& s1, const string& s2) {
        return s1 < s2;
    });
    for (const string& s : names)
        cout << s << endl;
}

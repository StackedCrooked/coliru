#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

using namespace std;

string reverse(string const& s) {
    cout << "reverse lvalue" << endl;
    return {s.rbegin(), s.rend()};
}

string reverse(string&& s) {
    cout << "reverse rvalue" << endl;
    std::reverse(s.begin(), s.end());
    return std::move(s);
}

int main() {
    string s ("abcdefg");
    
    cout << "=====" << endl;
    string s1 = reverse(s);           //copy
    cout << s1 << endl;
    cout << "=====" << endl;
    string s2 = reverse("abcdefg");//move
    cout << s2 << endl;
    cout << "=====" << endl;
    string s3 = reverse(std::move(s));//move
    cout << s3 << endl;
    cout << "=====" << endl;
}

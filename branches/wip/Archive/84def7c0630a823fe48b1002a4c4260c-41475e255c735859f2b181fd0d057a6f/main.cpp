#include <iostream>
#include <string>

using namespace std;

string const& createString(char c) {
    static string s(10, c);
    return s;
}

int main() {
    cout << createString('a') << ' ' << createString('z') << endl;
}
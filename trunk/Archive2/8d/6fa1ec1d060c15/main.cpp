#include <sstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string& str, char delim=' ') {
    stringstream ss(str);
    string tok;
    vector<string> vec;
    while (getline(ss, tok, delim)) {
        if (!tok.empty())
            vec.push_back(tok);
    }
    return vec;
}

int main() {
    string s = "aaa-bbb-cd-erb-tr--btr";
    
    for (string tok : split(s, '-')) {
        cout << tok << endl;
    }
}

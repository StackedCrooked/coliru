#include <sstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string& str) {
    stringstream ss(str);
    vector<string> vec {istream_iterator<string>{ss}, istream_iterator<string>{}};
    return vec;
}

int main() {
    string s = "        O    rato roeu a roupa do rei de roma             ";
    
    for (string tok : split(s)) {
        cout << tok << endl;
    }
}

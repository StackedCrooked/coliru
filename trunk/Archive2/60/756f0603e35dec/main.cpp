#include <string>

using namespace std;

int BruteForce(const string& line, const string& pattern) {
    const size_t n = line.length();
    const size_t m = pattern.length();

    if (n<m) return -1;

    for(size_t i = 0u; i <= (n - m); i++) {
        for(size_t j=0; j < m  && (line[i + j] == pattern[j]); ++j) {
            if(j == m-1) {
                return i;
            }
        }
    }
    return -1;
}

#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    string text, algo_type, pattern, fname, line;
    getline(cin ,text);
    istringstream iss(text);
    if(iss >>  algo_type  >>  pattern  >> fname) {
        cout << " " << algo_type  << " " << pattern <<  " " <<fname << "\n";
    }

    int i = 1;
    ifstream ifs;
    ifs.open(fname.c_str());
    while(getline(ifs, line) && fname != "") {
        if(algo_type == "bf") {
            cout << "Line " << i++ << ":" << BruteForce(line,pattern) << " '" << line << "'" << endl;
        }
    }
    return 0;
}

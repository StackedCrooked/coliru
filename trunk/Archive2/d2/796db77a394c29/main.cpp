#include <vector>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main() {
    const char* data = "[caminho da pasta]\0[arquivo 1]\0[arquivo 2]\0[arquivo 3]\0\0";
    
    vector<string> files;
    
    const char* str = data;
    int len = strlen(str);
    
    while (len) {
        files.push_back(string(str, len));
        str = str + len + 1;
        len = strlen(str);
    }
    
    for (unsigned i = 0; i < files.size(); ++i) {
        cout << "[" << i << "] = '" << files[i] << "'" << endl;
    }
    
    return 0;
}
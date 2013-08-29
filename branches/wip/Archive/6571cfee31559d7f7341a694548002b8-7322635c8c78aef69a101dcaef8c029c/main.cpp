#include <iostream>
#include <algorithm>
#include <map>

using std::map;
using std::string;
using std::make_pair;
using std::cout;

map<string, string> params;

int main(int argc, char* argv[])
{
    bool waitingForParam = true;
    string paramName;
    
    for (int i = 1; i < argc; ++i) {
        if (waitingForParam) {
            if (argv[i][0] == '-') { // new param 
                paramName = argv[i];
                waitingForParam = false;
            }
        }
        else {
            if (argv[i][0] == '-') { // empty value
                params.insert(make_pair(paramName, string()));
                paramName = argv[i];
            } else {
                params.insert(make_pair(paramName, string(argv[i])));
                waitingForParam = true;
            }
        }
    }
    
    auto exists = [&params](string const& param) {
        return (params.find(param) != params.end());
    };
    
    if (exists("-f")) {
        cout << "-f parameter present with value : " << params["-f"];
    }
}
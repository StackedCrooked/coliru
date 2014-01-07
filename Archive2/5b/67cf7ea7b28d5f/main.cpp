#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>

int main(int argc, char* argv[])
{
    using namespace std;
   
    vector<string> cmdlineargs(argv+1, argv+argc);
    string flag {};
   
    for(const auto &arg : cmdlineargs) {
        if (arg.front() == '-') {
            if( all_of(arg.begin(), arg.end(), [](char c){ return c == '-'; }) ) {
                cout << "Spurious flag " << arg << endl;
            }
            else {
                flag = arg.substr(arg.find_first_not_of("-", 0));
                cout << "*" << flag << "*" << endl;
            }
            continue;
        }
        
        cout << arg << endl;
    }
   
    return EXIT_SUCCESS;
} 
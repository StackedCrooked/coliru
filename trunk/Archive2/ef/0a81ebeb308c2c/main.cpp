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
            if( all_of(arg.cbegin(), arg.cend(), [](char c){ return c == '-'; }) ) {
                cout << "Spurious flag " << arg << endl;
                flag.clear();
            }
            else {
                flag = arg.substr(arg.find_first_not_of("-", 0));
                
                if( any_of(flag.cbegin(), flag.cend(), [](char c){ return c == '-'; }) ) {
                    cout << "ERROR: Dude.. this is too much " << flag << endl;
                    flag.clear();
                } else {
                    cout << "*" << flag << "*" << endl;
                }
            }
        } // flag?
        else {
            if( flag.size() > 0 ) 
                cout << "    ";
            cout << arg << endl;
        } // args
    } // range based for loop
   
    return EXIT_SUCCESS;
}


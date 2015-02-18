#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    stringstream stream1;
    stream1 << "2015-1111,Christian Karl,M\n";
    stream1 << "2015-1112,Joshua Evans,M\n";
    stream1 << "2015-1115,Jean Chloe,F\n";
    stream1 << "2015-1113,Shairene Traxe,F\n";
    stream1 << "2015-1114,Paul Howard,M\n";
    
    string line;
    while (std::getline(stream1, line)) {
        if (line.find("2015-1113") != string::npos) {
            cout << line << endl;
        }
        else {
            cout << "NOT FOUND!";
            break;
        }
    }
}
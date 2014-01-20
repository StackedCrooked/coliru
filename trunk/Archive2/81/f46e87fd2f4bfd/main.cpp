#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    map<string, string> myMap;
    
    if (myMap.find("hang_on") != myMap.end()) {
        cout << "this won't be reached" << endl;
    }
    
    if (myMap["hang_on"].length() > 0) {
        cout << "niether will this, but..." << endl;
    }
    
    if (myMap.find("hang_on") != myMap.end()) {
        cout << "woah!" << endl;
    }
}

#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
    map<int, string> data;
    data[1] = "one";
    data[2] = "two";
    data[10] = "ten";
    
    for (map<int, string>::iterator it = data.begin(); it != data.end(); ++it)
        cout << it->first << " " << it->second << endl;
}
        
    
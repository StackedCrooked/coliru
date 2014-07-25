#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

int main() {
    string testing[] = { "Test", "One", "Two", "Three"};
    string * stringArray;
    
    copy(begin(testing), end(testing), ostream_iterator<string>(cout, "\n"));
    cout << "------------------" << endl;
    
    stringArray = new string[5];
    stringArray[0] = "Test";
    
    copy(stringArray, stringArray+5, ostream_iterator<string>(cout, "\n"));
    cout << "------------------" << endl;
    
    stringArray[1] = testing[1];
    stringArray[2] = testing[2];
    copy(stringArray, stringArray+5, ostream_iterator<string>(cout, "\n"));
    cout << "------------------" << endl;
    return 0;
}
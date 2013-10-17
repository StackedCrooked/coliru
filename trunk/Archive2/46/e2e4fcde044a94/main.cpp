#include <map>
#include <unordered_map>
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

int main()
{
    unordered_map<string, int> dict;  // <KeyType, ValueType>
    
    dict["Mary"] = 10;
    
    
    pair<string, int> entry("Sandy",30);
    dict.insert(entry);
    
    dict.insert(make_pair("John",20));

    if( dict.insert(make_pair("John",40)).second ) {
        cout << "John inserted";
    } else {
        cout << "John already there";
    }


}
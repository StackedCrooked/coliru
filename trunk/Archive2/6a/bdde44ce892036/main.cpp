#include <map>
#include <unordered_map>
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

void print(pair<string, int> p)
{
    cout << p.first << " " << p.second << endl;
}

int main()
{
    unordered_map<string,int> dict;
    unordered_map<string,int>::iterator it;
    
    dict["a"]=50;
    dict["b"]=100;
    dict["c"]=150;
    dict["d"]=200;
    
    it=dict.find("b");
    if( it == dict.end() ) cout << "not found";
    
    dict.erase(it);
     
    // dangerous!
    dict.erase(dict.find("c"), dict.end());

    for_each(dict.begin(), dict.end(), print);
}
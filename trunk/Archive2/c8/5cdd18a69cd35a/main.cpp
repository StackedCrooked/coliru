//: C05:Accumulate.cpp
// Passes a "function" as a parameter at compile time.
#include <iostream>
#include <map>
#include <algorithm>
#include <numeric>
using std::cout;
using std::endl;
using std::map;

int getSecond(int i, const std::pair<char,int>& thePair) { return i + thePair.second; }

#define YAHOO

#ifdef YAHOO2
void bar() {
    cout << "2\n";   
}
#else
void bar() {
    cout << "1\n";   
}
#endif
 
int main() {
    std::map<char,int> theMap;
    theMap['A'] = 5;
    theMap['C'] = 6;
    theMap['G'] = 3;
    cout << "total " << std::accumulate(theMap.begin(), theMap.end(), 0, getSecond) << std::endl;
    bar();
}

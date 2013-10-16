#include <set>
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

int main()
{
    string str = "Hello";
    
    str[3] = 'M';
    
    cout << str << endl;   // HelMo
    
    
    for(size_t i=0; i<str.size(); ++i)
        cout << str[i] << '-';
}
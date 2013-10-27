#include <map>
#include <set>
#include <vector>
#include <list>
#include <unordered_map>
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;
using namespace std::placeholders;


bool is_odd(int n) {
return (n % 2) != 0;
}








int main()
{
     
    string arr[] = { "Jess", "Anne", "Sandra", "Hugh", "Nick" };
    
    set<string> s(arr, arr+5);

    vector<string> v;
    v.resize(s.size());

    v.resize( s.size() );
    vector<string>::iterator dest = v.begin();
    set<string>::iterator src = s.begin();
    while( src != s.end() )
    {
        *dest = *src;
        ++src;
        ++dest;
    }


    for(auto n : v )
        cout << n << " ";
    cout << endl;
}
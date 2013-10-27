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






int main()
{
     
    string arr[] = { "Jess", "Anne", "Sandra", "Hugh", "Nick" };
    
    set<string> s(arr, arr+5);

    vector<string> v;
    

    v.reserve(s.size());
    std::copy(s.begin(), s.end(), back_inserter(v));



    for(auto n : v )
        cout << n << " ";
    cout << endl;
}
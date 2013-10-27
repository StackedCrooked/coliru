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
     
    map<string, int> s = { {"Jess",1}, {"Anne",2}, {"Sandra",3}, {"Hugh",4}, {"Nick",5} };

    set<string> v;
        
    
    std::transform(s.begin(), s.end(), 
                    inserter(v, v.begin()), 
                    bind(&map<string,int>::value_type::first, _1) );
                    
    for(auto n : v )
        cout << n << " ";
    cout << endl;
}
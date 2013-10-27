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





string append_int_to_string ( pair<string, int>  p ) {
    return p.first + to_string(p.second);
}


int main()
{
     
    map<string, int> m = { {"Jess",1}, {"Anne",2}, {"Sandra",3}, {"Hugh",4}, {"Nick",5} };

    set<string> v;
        
    
    std::transform( m.begin(), m.end(),
                inserter(v, v.begin()),
                bind( append_int_to_string, _1) );

                    
    for(auto n : v )
        cout << n << " ";
    cout << endl;
}
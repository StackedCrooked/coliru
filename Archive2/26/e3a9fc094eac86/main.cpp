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





string append_int_to_string ( string s, int i ) {
    return s + to_string(i);
}


int main()
{
     
    map<string, int> m = { {"Jess",1}, {"Anne",2}, {"Sandra",3}, {"Hugh",4}, {"Nick",5} };

    set<string> v;
        
    
    std::transform( m.begin(), m.end(),
                    inserter(v, v.begin()),
                    bind( append_int_to_string, 
                            bind( &map<string,int>::value_type::first, _1),
                            bind( &map<string,int>::value_type::second, _1)
                        )
                    );

                    
    for(auto n : v )
        cout << n << " ";
    cout << endl;
}
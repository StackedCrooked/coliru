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





bool is_odd( int x ) {
    return x % 2; 
}



int main()
{
     
    vector<int> src = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    set<int> dest;
        
    
    std::copy_if( src.begin(), src.end(),
                  inserter(dest, dest.begin()),
                  bind( std::logical_and<bool>(),
                    bind(is_odd, _1),
                    bind(std::greater<int>(), _1, 4)
                   )

                );

                    
    for(auto n : dest )
        cout << n << " ";
    cout << endl;
}
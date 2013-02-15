#include <limits>
#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;


int main()
{    
    std::vector<int> v;
    for(unsigned i = 0; i< 100; ++i)
        v.push_back(i);
        
    std::sort(v.begin(), v.end(), [](const int&, const int&)->bool { return false; });
    
    for(auto const& i: v)
        cout<<i<<' ';
}
#include <limits>
#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <algorithm>
#include <type_traits>

using std::cout;
using std::endl;

void mutator(int& n) { ++n; cout<<n<<endl; }
void non_mutator(const int& n) { cout<<n<<endl; }

int main()
{    
    std::vector<int> v;
    for(unsigned i = 0; i< 1; ++i)
        v.push_back(i);
    
    //for(auto&& i: v)
    //    mutator(i);
        
    for(auto&& i: v)
    {
        cout<<std::boolalpha<<std::is_const<std::remove_reference<decltype(i)>::type>::value<<endl;
        non_mutator(i);
    }
    
    for(auto const& i: v)
    {
        cout<<std::boolalpha<<std::is_const<std::remove_reference<decltype(i)>::type>::value<<endl;
        non_mutator(i);
    }
        
    cout<<endl;
}
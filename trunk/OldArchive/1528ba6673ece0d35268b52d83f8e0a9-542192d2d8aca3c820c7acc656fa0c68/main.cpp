#include <vector>
#include <utility>

template <template<typename...> class R=std::vector, 
          typename Top, 
          typename Sub = typename Top::value_type> 
   R<typename Sub::value_type> flatten(Top const& all)
{
    using std::begin;
    using std::end;

    R<typename Sub::value_type> accum;
    
    for(auto& sub : all)
        accum.insert(end(accum), begin(sub), end(sub));
        
    return accum;
}

/// demo
#include <iostream>

int main()
{
    const std::vector<std::vector<int> > top { 
        { 1,2,3 }, { 9,99,999 } };

    auto z = flatten(top);    
    
    for (auto i : z)
       std::cout << i << " ";
}

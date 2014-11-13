#include <memory>
#include <vector>
#include <iostream>

#include <boost/iterator/indirect_iterator.hpp>

int main()
{
    std::vector<std::unique_ptr<int>> vec;
    
    for (int i : {1, 2, 3})
       vec.emplace_back( new auto(i) );
       
    using iterator = boost::indirect_iterator<decltype(vec)::iterator>;
    iterator iter = vec.begin(),
             end = vec.end();
    
    while (iter != end)
        std::cout << *iter++ << ", ";
}

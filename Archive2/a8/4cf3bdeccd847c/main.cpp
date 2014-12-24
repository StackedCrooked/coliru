#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> vec={1,2,3,4,5};
    
    const int offset=0;
    std::cout<< std::accumulate(vec.begin(),vec.end(),offset);
}
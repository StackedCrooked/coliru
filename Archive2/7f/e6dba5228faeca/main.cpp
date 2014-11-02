#include <list>
#include <map>
#include <algorithm>
#include <iostream>

int main()
{
    std::map<int, int> map{ {1, 2}, {2, 3} };
    std::list<std::map<int, int>::const_iterator> list;
    
    list.resize(map.size());
    std::iota( std::begin(list), std::end(list), std::begin(map) );
    
    for (auto iter : list)
    std::cout << iter->first << ' ' << iter->second << '\n';
}
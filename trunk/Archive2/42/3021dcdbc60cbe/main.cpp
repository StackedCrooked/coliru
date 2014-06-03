#include <algorithm>
#include <iostream>
#include <list>
#include <set>




int main()
{
    std::list<int> list = { 4, 7, 3, 8, 2, 9, 1, 0 };    
    
    std::set<int> set;
    while (!list.empty())
    {
        set.insert(std::move(list.front()));
        list.pop_front();
    }
    std::move(begin(set), end(set), inserter(list, begin(list)));
    
    for (int n : list) std::cout << n << ' ';
}

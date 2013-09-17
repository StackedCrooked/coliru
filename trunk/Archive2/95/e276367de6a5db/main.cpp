#include <iostream>
#include <algorithm>
#include <set>
 
template<class ForwardIt>
void unique_inc(ForwardIt& it)
{
    ForwardIt old = it++;
    while (*it == *old) ++it;
}
 
int main() 
{
    std::multiset<int> v{1, 2, 2, 2, 3, 3, 1, 1, 2, 2, 3, 3, 4};
 
    for (std::multiset<int>::iterator it = v.begin(); it != v.end(); unique_inc(it)) {
        std::cout << *it << ": " << v.count(*it) << "\n";
    }
}
#include <algorithm>
#include <list>
#include <set>


int main()
{
    std::list<int> l = { 4, 7, 3, 8, 2, 9, 1, 0 };
    
    std::set<int> s;
    
    std::move(l.begin(), l.end(), [&](int n) {
        s.insert(std::move(n));
    });
}

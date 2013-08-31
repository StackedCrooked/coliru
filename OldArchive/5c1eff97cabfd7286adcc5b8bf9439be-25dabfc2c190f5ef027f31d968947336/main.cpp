#include <utility>

template < typename T, typename... Args >
auto emplace(T& c, Args&&... pp) -> decltype(c.emplace_back(std::forward<Args>(pp)...))
{
    return c.emplace_back(std::forward<Args>(pp)...);
}

template < typename T, typename... Args >
auto emplace(T& c, Args&&... pp, ...) -> decltype(c.emplace(std::forward<Args>(pp)...))
{
    return c.emplace(std::forward<Args>(pp)...);
}

#include <queue>
#include <stack>
#include <deque>
#include <list>
#include <set>
#include <vector>

int main()
{
    std::queue<int> q;
    std::stack<int> st;
    std::deque<int> d;
    std::list<int> l;
    std::set<int> s;
    std::vector<int> v;
    
    emplace(q, 42);
    emplace(st, 42);
    emplace(d, 42);
    emplace(l, 42);
    emplace(s, 42);
    emplace(v, 42);
    emplace(s);
}

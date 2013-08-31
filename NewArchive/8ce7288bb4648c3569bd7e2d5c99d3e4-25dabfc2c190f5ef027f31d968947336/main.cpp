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

#include <set>
#include <vector>

int main()
{
    std::set<int> s;
    std::vector<int> v;
    
    emplace(s, 42);
    emplace(v, 42);
    emplace(s);
}

#include <utility>

/*
// illegal context for `...`
template<class Cont, class... Args>
void emplace_all(Cont& c, Args&&... args)
{
    c.emplace_back(std::forward<Args>(args))...;
}
*/
template<class Cont, class... Args>
void emplace_all(Cont& c, Args&&... args)
{
    int unused[] = {(c.emplace_back(std::forward<Args>(args)), 0)...};
}

#include <vector>
#include <iostream>

int main()
{
    std::vector<int> v;
    emplace_all(v, 1,2,3,4);
    for(auto const& e : v)
    {
        std::cout << e << ',';
    }
}

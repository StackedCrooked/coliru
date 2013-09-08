#include <utility>

/*
// illegal context for `...`
template<class Cont, class... Args>
void emplace_all(Cont& c, Args&&... args)
{
    c.emplace_back(std::forward<Args>(args))...;
}
*/

template<class Cont, class Arg>
int emplace_back(Cont& c, Arg&& arg)
{
    c.emplace_back(std::forward<Arg>(arg));
    return 42;
}

template<class Cont, class... Args>
void emplace_all2(Cont& c, Args&&... args)
{
    int unused[] = {emplace_back(c, std::forward<Args>(args))...};
}

#include <vector>
#include <iostream>

int main()
{
    std::vector<int> v;
    emplace_all2(v, 1,2,3,4);
    for(auto const& e : v)
    {
        std::cout << e << ',';
    }
}

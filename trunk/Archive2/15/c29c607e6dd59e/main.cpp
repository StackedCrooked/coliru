#include <map>
#include <utility>
#include <iostream>

int main()
{
    std::multimap<int, std::string> m{ {4, "X"}, {5, "A"}, {5,"B"}, {5,"C"} };
    
    auto its = m.equal_range(5);
        
    struct iter_range
    {
        decltype(its) p;
        auto begin() -> decltype(p.first) { return p.first; }
        auto end() -> decltype(p.second) { return p.second; }
    };

    for (auto p : iter_range{its})
    {
        std::cout << p.first << " " << p.second << std::endl;
    }
}

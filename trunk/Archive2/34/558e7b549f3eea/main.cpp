#include <map>
#include <memory>
#include <algorithm>
#include <iostream>

int main()
{    
    std::map<int, std::unique_ptr<int>> m;
    m[0] = std::make_unique<int>(42);
    m[1] = std::make_unique<int>(1337);
    m[2] = std::make_unique<int>(1729);

    auto it = std::find_if(std::begin(m), 
                           std::end(m), 
                           [] (decltype(m)::value_type const& entry)
    {
        return *(entry.second) == 1337;
    });

    if (it != std::end(m)) { std::cout << it->first; }
}
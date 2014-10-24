#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

using Type = std::vector<std::string>;

Type one = {"1", "2"};

std::unordered_map<std::string, const std::reference_wrapper<Type>> _map = {
    {"first", std::ref(one) },
};


int main(void)
{
    // works
    auto & p = _map.at("first");
    for (auto & i : p.get())
        std::cout << i << std::endl;
        
    std::reference_wrapper a = std::ref(one);
        
}

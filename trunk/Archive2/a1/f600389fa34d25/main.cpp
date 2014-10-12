#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>

int main()
{
    std::unique_ptr<int> p[10]{std::make_unique<int>(42)};
    
    auto set_value = [](std::unique_ptr<int>& p, auto value)
    {
        *p = value;
        return p;
    };
    
    std::generate(std::begin(p), std::end(p),
        std::bind(set_value, std::placeholders::_1, 40));
    
    return 0;
}
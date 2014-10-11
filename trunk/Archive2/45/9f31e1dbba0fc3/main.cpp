#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>

int main()
{
    int* p[10];
    auto set_value = [](auto p, auto value)
    {
        *p = value;
        return p;
    };
    std::transform(std::begin(p), std::end(p), std::begin(p),
        std::bind(set_value, 40));
    
    return 0;
}
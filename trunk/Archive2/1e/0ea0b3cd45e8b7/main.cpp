#include <cstddef>
#include <iostream>
#include <limits>

class Vector
{
    std::size_t s_;    
public:
    explicit constexpr Vector(std::size_t n): s_{n} {}
    constexpr auto size() const { return s_; }
};

int main()
{
    auto constexpr v = Vector{static_cast<std::size_t>(std::numeric_limits<unsigned>::max()) + 1};
    for (auto i = 0u; i < v.size(); ++i) // ERROR, infinite loop
        std::cout << i;
}

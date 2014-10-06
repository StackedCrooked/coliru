#include <iostream>
#include <memory>

struct X
{
    X() = default;
    X(const X&) = delete;
    X(X&&) = default;
    
    float operator()() const noexcept;
};

#include <functional>

std::function<float()> xf;

int main()
{
    xf = X{};
}
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

struct X
{
public:
    X() { }
    X(X const&) { std::cout << "Copied!" << std::endl; }
    X(X&& other) { x = 42; other.x = 0; std::cout << "Moved!" << std::endl; }
public:
    int x = 42;
};

int main()
{
    std::vector<X> v(5);
    
    std::vector<X> result;
    std::transform(std::begin(v), std::end(v), std::back_inserter(result),
        [&] (X& x) -> X
    {
        return std::move(x);
    });
    
    for (auto& x : v) { std::cout << x.x << std::endl; }
}

#include <memory>
#include <utility>
#include <map>
#include <iostream>
#include <cassert>

int main()
{
    typedef std::unique_ptr<int> T;
    T x(new int(1)), y(new int(2));
    
    std::cout << y.get() << '\n';
    
    std::map<int, T> m;
    
    m.emplace(1, std::move(x));
    auto it = m.emplace(1, std::move(y));
    
    assert(!it.second);
    std::cout << y.get() << '\n';
}
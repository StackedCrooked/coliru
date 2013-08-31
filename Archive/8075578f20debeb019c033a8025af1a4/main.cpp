#include <iostream>
#include <unordered_map>
#include <utility>

struct foo {
    int const x;
    
    bool operator ==(foo const& that) const { return x == that.x; }
    
    foo(int x) : x(x) { }
};

int main() {
    auto hash = [](foo const& f) { return f.x; };
    std::unordered_map<foo, int, decltype(hash)> mymap(0, hash);
    
    mymap.emplace(std::make_pair(foo(42), 23));
    std::cout << mymap[foo(42)] << '\n';
}
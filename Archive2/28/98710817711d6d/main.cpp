#include <iostream>
#include <algorithm>
#include <utility>

template <typename Tp>
struct Container {
    Tp something;
    
    Container(Tp val) : something(val) {}

    operator Tp() {
        return something;
    }
};


template <typename Tp>
std::hash<Tp> make_hash(Container<Tp> cont) {
    return std::hash<Tp>();
}

int main() {
    Container<int> x(1);
    std::hash<int> hasher = make_hash(x);
    hasher(x);    
    
    return 0;
}
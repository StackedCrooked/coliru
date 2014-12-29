#include <initializer_list>
#include <iostream>

template <typename V>
struct Weighted_edge {
    V source;
    V dest;
    int weight;
    // can't maintain as POD because V might not be POD
    Weighted_edge(V u, V v, int w) : source{u}, dest{v}, weight{w} {} 
    int get_weight() const {return weight;}
};
template <typename V>
struct Unweighted_edge {
    V source;
    V dest;
    Unweighted_edge(V u, V v) : source{u}, dest{v} {} 
    int get_weight() const {return 1;}
};

template<typename V>
struct foo{
    foo(std::initializer_list<Weighted_edge<V>>) {std::cout << __PRETTY_FUNCTION__ << std::endl; }
    foo(std::initializer_list<Unweighted_edge<V>>) {std::cout << __PRETTY_FUNCTION__ << std::endl; }
};


int main() {
    foo<int> g {{1,2}, {2,3}, {3,4}, {4,1}};
}
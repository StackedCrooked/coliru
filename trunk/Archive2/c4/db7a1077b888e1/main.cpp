#include <map>
#include <vector>

struct B { virtual ~B() = default; };
template <typename T> struct D : B { };

B* makeD() {
    switch(rand()%4) {
        case 0: return new D<int>;
        case 1: return new D<double>;
        case 2: return new D<std::string>;
        case 3: return new D<D<int> >;
    }
}

#include <typeinfo>
#include <string>

std::map<std::string, std::vector<B*> > split(std::vector<B*> const& bs) {
    std::map<std::string, std::vector<B*> > m;
    for(auto b : bs)
        m[typeid(*b).name()].push_back(b);
    return m;
}

#include <algorithm>
#include <iterator>
#include <iostream>

int main() {
    std::vector<B*> v;
    std::generate_n(back_inserter(v), 100, makeD);

    for (auto const& e : split(v))
        std::cout << "Type: " << e.first << ", " << e.second.size() << " entries\n";
}

